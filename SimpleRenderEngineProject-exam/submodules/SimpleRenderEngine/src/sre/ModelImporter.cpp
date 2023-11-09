/*
 *  SimpleRenderEngine (https://github.com/mortennobel/SimpleRenderEngine)
 *
 *  Created by Morten Nobel-Jørgensen ( http://www.nobel-joergensen.com/ )
 *  License: MIT
 */

#include "sre/ModelImporter.hpp"
#include "sre/Color.hpp"
#include <algorithm>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <cerrno>
#include <cctype>
#include <unordered_map>
#include "sre/Mesh.hpp"
#include "sre/Log.hpp"
#include <unordered_map>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include "glm/glm.hpp"

using namespace std;
using namespace glm;

// anonymous namespace
namespace {

    // trim from start (in place)
    inline void ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
            return !std::isspace(ch);
        }));
    }

    // trim from end (in place)
    inline void rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
            return !std::isspace(ch);
        }).base(), s.end());
    }

    // trim from both ends (in place)
    inline void trim(std::string &s) {
        ltrim(s);
        rtrim(s);
    }

    std::string kPathSeparator =
#ifdef _WIN32
            "\\";
#else
            "/";
#endif

	std::string kNonPathSeparator =
#ifndef _WIN32
            "\\";
#else
            "/";
#endif

    // from http://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
    string getFileContents(const string& filename)
    {
        ifstream in{filename, ios::in | ios::binary};
        if (in)
        {
            std::string contents;
            in.seekg(0, std::ios::end);
            auto size = in.tellg();
            if (size>0){
                contents.resize((string::size_type)size);
                in.seekg(0, std::ios::beg);
                in.read(&contents[0], contents.size());
            }
            in.close();
            return contents;
        }
        LOG_ERROR("Error reading %s. Error code: %i",filename.c_str(), errno);
        return "";
    }

    std::string concat(std::vector<std::string> v, int from){
        std::string res = v[from];
        for (int i=from+1;i<v.size();i++){
            res += " ";
            res += v[i];
        }
        trim(res);
        return res;
    }

    std::string fixPathEnd(std::string &path){
        char lastChar = path[path.length()-1];
        if (lastChar != kPathSeparator[0]){
            return path + kPathSeparator;
        }
        return path;
    }

    std::string replaceAll( string &s, const string& search, const string& replace ) {
        for( size_t pos = 0; ; pos += replace.length() ) {
            // Locate the substring to replace
            pos = s.find( search, pos );
            if( pos == string::npos ) break;
            // Replace by erasing and inserting
            s.erase( pos, search.length() );
            s.insert( pos, replace );
        }
        return s;
    }


    std::string fixPath(std::string path){
        replaceAll( path, kNonPathSeparator, kPathSeparator);
        replaceAll( path, kPathSeparator +"."+ kPathSeparator, kPathSeparator);
        replaceAll( path, "\r", "");
        return path;
    }

    vec4 toVec4(vector<string> &tokens){
        vec4 res{0,0,0,1};
        for (int i=0;i<4;i++){
            if (i+1 < tokens.size()){
                res[i] = (float)atof(tokens[i+1].c_str());
            }
        }
        return res;
    }

    vec3 toVec3(vector<string> &tokens){
        vec3 res{0,0,0};
        for (int i=0;i<3;i++){
            if (i+1 < tokens.size()){
                res[i] = (float)atof(tokens[i+1].c_str());
            }
        }
        return res;
    }

    sre::Color toColorRGB(vector<string> &tokens){
        sre::Color res{0,0,0};
        for (int i=0;i<3;i++){
            if (i+1 < tokens.size()){
                res[i] = (float)atof(tokens[i+1].c_str());
            }
        }
        return res;
    }

    // replace first occurrence of from in str with to
    bool replace(std::string& str, const std::string& from, const std::string& to) {
        size_t start_pos = str.find(from);
        if(start_pos == std::string::npos)
            return false;
        str.replace(start_pos, from.length(), to);
        return true;
    }

    struct ObjGroup {
        int faceIndex;
        std::string name;
    };

    struct SmoothGroup {
        int faceIndex;
        int smoothGroupIdx; // 0 means none
    };

    struct ObjVertex {
        int vertexPositionIdx;
        int textureIdx;
        int normalIdx;
    };
    typedef std::vector<ObjVertex> ObjFace;

    enum class ObjIlluminationMode {
        Mode0 = 0, // Color on and Ambient off
        Mode1 = 1, // Color on and Ambient on
        Mode2 = 2, // Highlight on
        Mode3 = 3, // Reflection on and Ray trace on
        Mode4 = 4, // Transparency: Glass on, Reflection: Ray trace on
        Mode5 = 5, // Reflection: Fresnel on and Ray trace on
        Mode6 = 6, // Transparency: Refraction on, Reflection: Fresnel off and Ray trace on
        Mode7 = 7, // Transparency: Refraction on, Reflection: Fresnel on and Ray trace on
        Mode8 = 8, // Reflection on and Ray trace off
        Mode9 = 9, // Transparency: Glass on, Reflection: Ray trace off
        Mode10 = 10 // Casts shadows onto invisible surfaces
    };

    enum class ObjTextureMapType {
        Diffuse, // map_Kd
        Ambient, // map_Ka
        Specular, // map_Ks
        SpecularCoeficient, // map_Ns
        Transparancy, // map_d or map_Tr
        Bump, // map_bump or bump
        Displacement, // disp
        StencilDecal // decal
    };

    struct ObjTextureMap {
        std::string filename;
        ObjTextureMapType type;
    };

    struct ObjMaterial {
        std::string name;
        sre::Color ambientColor; // Ka
        sre::Color diffuseColor; // Kd
        sre::Color specularColor; // Ks
        float specularCoefficient; // Ns
        float transparent; // d or Tr
        std::vector<ObjIlluminationMode> illuminationModes;
        std::vector<ObjTextureMap> textureMaps;
    };



    struct ObjMaterialChange {
        int faceIndex;
        std::string name;
    };

    ObjFace toObjFace(vector<string> &tokens){
        ObjFace res;
        for (int i=1; i<tokens.size(); i++) {
            string & p = tokens[i];
            replace(p, "//","/0/");

            ObjVertex o{0,0,0};

            stringstream ss{p};
            char buffer[50];

            ss.getline(buffer,50, '/');
            o.vertexPositionIdx = atoi(buffer);
            if (ss.good()){
                ss.getline(buffer,50, '/');
                o.textureIdx = atoi(buffer);
            }
            if (ss.good()){
                ss.getline(buffer,50, '/');
                o.normalIdx = atoi(buffer);
            }
            res.push_back(o);
        }
        return move(res);
    }

    void parseMaterialLib(std::string & materialLib, std::vector<ObjMaterial>& materials){
        const int bufferSize = 256;
        char buffer[bufferSize];
        char buffer2[bufferSize];
        stringstream ss{materialLib};

        while (ss.good()){
            ss.getline(buffer, bufferSize);
            stringstream likeTokensizer{buffer};
            vector<string> tokens;
            while (likeTokensizer.good()) {
                likeTokensizer.getline(buffer2, bufferSize, ' ');
                tokens.emplace_back(buffer2);
            }
            if (tokens.empty()){
                continue;
            }
            if (tokens[0] == "newmtl"){
                sre::Color zero{0,0,0};
                auto name = concat(tokens,1);
                ObjMaterial material{replaceAll(name,"\r",""),zero,zero,zero,50,1};
                materials.push_back(material);
            } else {
                if (materials.empty()){
                    continue;
                }
                ObjMaterial & currentMat = materials.back();
                if (tokens[0] == "Ka"){
                    currentMat.ambientColor = toColorRGB(tokens);
                } else if (tokens[0] == "Kd"){
                    currentMat.diffuseColor = toColorRGB(tokens);
                } else if (tokens[0] == "Ks"){
                    currentMat.specularColor = toColorRGB(tokens);
                } else if (tokens[0] == "d"){
                    currentMat.transparent = (float)atof(tokens[1].c_str());
                } else if (tokens[0] == "illum"){
                    int illumMode = atoi(tokens[1].c_str());
                    currentMat.illuminationModes.push_back(static_cast<ObjIlluminationMode>(illumMode));
                } else if (tokens[0] == "map_Ka"){
                    currentMat.textureMaps.push_back({tokens[1], ObjTextureMapType::Ambient});
                } else if (tokens[0] == "map_Kd"){
                    currentMat.textureMaps.push_back({tokens[1], ObjTextureMapType::Diffuse});
                } else if (tokens[0] == "map_Ks"){
                    currentMat.textureMaps.push_back({tokens[1], ObjTextureMapType::Specular});
                } else if (tokens[0] == "map_Ns"){
                    currentMat.textureMaps.push_back({tokens[1], ObjTextureMapType::SpecularCoeficient});
                } else if (tokens[0] == "map_d"){

                } else if (tokens[0] == "map_bump" || tokens[0] == "bump" ){
                    currentMat.textureMaps.push_back({tokens[1], ObjTextureMapType::Bump});
                } else if (tokens[0] == "map_disp" || tokens[0] == "disp" ){
                    currentMat.textureMaps.push_back({tokens[1], ObjTextureMapType::Displacement});
                } else if (tokens[0] == "map_decal" || tokens[0] == "decal" ){

                }
            }
        }
    }

    struct ObjVertexHash {
        std::size_t operator()(const ObjVertex& k) const {
            return (( k.vertexPositionIdx << 16 ) ^ ( k.textureIdx << 8 )) ^ k.normalIdx;
        }
    };

    struct ObjVertexEqual {
        bool operator()(const ObjVertex& lhs, const ObjVertex& rhs) const {
            return lhs.vertexPositionIdx == rhs.vertexPositionIdx &&
                   lhs.textureIdx == rhs.textureIdx &&
                   lhs.normalIdx == rhs.normalIdx;
        }
    };
    using ObjVertexHashTable = std::unordered_map<ObjVertex,int,ObjVertexHash, ObjVertexEqual>;

    int getCreateIndex(ObjVertex &vertexIndex, int nextIndex, ObjVertexHashTable& usedVertices){
        auto pos = usedVertices.find(vertexIndex);
        if (pos != usedVertices.end()){
            return pos->second;
        }
        usedVertices.emplace(vertexIndex, nextIndex);
        return nextIndex;
    }

    struct ObjInterleavedIndex {
        std::string materialName;
        std::vector<uint32_t> vertexIndices;
    };

    shared_ptr<sre::Material> createMaterial(const std::string& materialName, const std::vector<ObjMaterial>& matVector, std::string path) {
        if (matVector.empty()){
            auto shader = sre::Shader::getStandardBlinnPhong();
            auto mat = shader->createMaterial();
            return mat;
        }
        const ObjMaterial* foundMat = nullptr;
        for (auto & v : matVector){
            if (v.name == materialName
                || materialName.empty()){ // empty is used for default material
                foundMat = &v;
                break;
            }
        }
        if (foundMat == nullptr){
            LOG_WARNING("Could not find material ",materialName.c_str());
            foundMat = matVector.data();
        }
        auto shader = sre::Shader::getStandardBlinnPhong();
        auto mat = shader->createMaterial();

        mat->setColor(foundMat->diffuseColor);

        mat->setSpecularity({foundMat->specularColor.r,foundMat->specularColor.g,foundMat->specularColor.b,foundMat->specularCoefficient});
        auto name = materialName;
        for (auto & map :foundMat->textureMaps){
            if (map.type == ObjTextureMapType::Diffuse){
                mat->setTexture(sre::Texture::create().withFile(fixPath(path+map.filename)).build());
                name+=" "+map.filename;
            }
        }
        mat->setName(name);
        return mat;
    }

}

std::shared_ptr<sre::Mesh> sre::ModelImporter::importObj(std::string path, std::string filename){
    std::vector<std::shared_ptr<Material>> outModelMaterials;
    return sre::ModelImporter::importObj(path, filename, outModelMaterials);
}

std::shared_ptr<sre::Mesh> sre::ModelImporter::importObj(std::string path, std::string filename, std::vector<std::shared_ptr<Material>>& outModelMaterials) {
    path = fixPathEnd(path);
    string file = getFileContents(path+filename);

    std::vector<glm::vec3> vertexPositions;
    std::vector<glm::vec4> textureCoords;
    std::vector<glm::vec3> normals;
    std::vector<ObjFace> faces;
    std::vector<ObjGroup> namedObjects;
    std::vector<ObjGroup> polygonGroups;
    std::vector<SmoothGroup> smoothGroups;
    std::vector<ObjMaterialChange> materialChanges;
    std::vector<ObjMaterial> materials;

    stringstream ss{file};
    const int bufferSize = 256;
    char buffer[bufferSize];
    char buffer2[bufferSize];
    while (ss.good()){
        ss.getline(buffer, bufferSize);
        stringstream likeTokensizer{buffer};
        vector<string> tokens;
        while (likeTokensizer.good()) {
            likeTokensizer.getline(buffer2, bufferSize, ' ');
			int buffer2Length = static_cast<int>(strlen(buffer2));
            for (int i=0;i<buffer2Length;i++){
                if (isspace(buffer2[i])){
                    buffer2[i] = '\0';
                }

            }
            tokens.emplace_back(buffer2);
        }
        if (tokens.empty()){
            continue;
        }
        int currentIndex = static_cast<int>(faces.size()) + 1;
        if (tokens[0] == "#"){                                          // comment
            // ignore
        } else if (tokens[0] == "v"){                                   // vertex position
            vec3 vertexPosition = toVec3(tokens);
            vertexPositions.push_back(vertexPosition);
        } else if (tokens[0] == "vt"){                                  // vertex texture coordinates
            vec4 textureCoord = toVec4(tokens);
            textureCoords.push_back(textureCoord);
        } else if (tokens[0] == "vn"){                                  // vertex normal
            vec3 normal = toVec3(tokens);
            normals.push_back(normal);
        } else if (tokens[0] == "f"){                                   // face
            faces.push_back(toObjFace(tokens));
        } else if (tokens[0] == "mtllib"){                              // material library
            string materialLib = getFileContents(fixPath(path+tokens[1]));
            parseMaterialLib(materialLib, materials);
        } else if (tokens[0] == "usemtl"){                              // use material
            materialChanges.push_back({currentIndex, concat(tokens,1)});
        } else if (tokens[0] == "o"){                                   // named object
            namedObjects.push_back({currentIndex, tokens[1]});
        } else if (tokens[0] == "g"){                                   // polygon group
            polygonGroups.push_back({currentIndex, tokens[1]});
        } else if (tokens[0] == "s"){                                   // smoothing groups
            int smoothingGroup = 0;                                     // 0 = no smoothing
            if (tokens[1] != "off"){
                smoothingGroup = atoi(tokens[1].c_str());
            }
            smoothGroups.push_back({currentIndex, smoothingGroup});
        }
    }

    int vertexCount = 0;
    int faceCount = 0;

    std::vector<ObjInterleavedIndex> indices;
    ObjInterleavedIndex * currentIndex = nullptr;
    auto materialChange = materialChanges.cbegin();
    bool includeTextureCoordinates = !textureCoords.empty();
    bool includeNormals = !normals.empty();
    ObjVertexHashTable usedVertices{42,ObjVertexHash{}, ObjVertexEqual{}};
    std::vector<glm::vec3> finalPositions;
    std::vector<glm::vec4> finalTextureCoordinates;
    std::vector<glm::vec3> finalNormals;
    bool firstFace = true;
    for (auto & face : faces){
        faceCount++;
        if (materialChange != materialChanges.end() || firstFace){
            if (firstFace && materialChange == materialChanges.end()){
                indices.push_back({"", {}});
                currentIndex = &indices.back();
            }
            else if (materialChange->faceIndex == faceCount){
                bool foundMaterial = false;
                for (auto & idx : indices) {
                    if (idx.materialName == materialChange->name){
                        foundMaterial = true;
                        currentIndex = &idx;
                        break;
                    }
                }
                if (!foundMaterial){
                    indices.push_back({materialChange->name, {}});
                    currentIndex = &indices.back();
                }
                materialChange++;
            }
            firstFace = false;
        }

        for (int i=2;i < face.size();i++){
            int triangle[] = {0, i-1, i};
            for (int triangleIndex : triangle){
                auto & vertexIndexObject = face[triangleIndex];
                int vertexIndex = getCreateIndex(vertexIndexObject, vertexCount, usedVertices);
                bool existInInterleavedData = vertexIndex != vertexCount;
                if (!existInInterleavedData){
                    // read data
                    vec3 vertexPosition = vertexPositions[vertexIndexObject.vertexPositionIdx - 1];
                    vec4 textureCoord{0,0,0,0};
                    if (vertexIndexObject.textureIdx > 0 && includeTextureCoordinates){
                        textureCoord = textureCoords[vertexIndexObject.textureIdx - 1];
                    }
                    vec3 normal;
                    if (vertexIndexObject.normalIdx > 0 && includeNormals){
                        normal = normals[vertexIndexObject.normalIdx-1];
                    }
                    // write interleaved data
                    finalPositions.push_back(vertexPosition);
                    if (includeTextureCoordinates){
                        finalTextureCoordinates.push_back(textureCoord);
                    }
                    if (includeNormals){
                        finalNormals.push_back(normal);
                    }
                    vertexCount++;
                }
                currentIndex->vertexIndices.emplace_back(vertexIndex);
            }
        }
    }

    // remove unused materials
    indices.erase(std::remove_if(indices.begin(), indices.end(), [](const ObjInterleavedIndex &a){ return a.vertexIndices.size()==0;}),
                  indices.end());

    auto&& meshBuilder = Mesh::create();
    meshBuilder.withPositions(finalPositions);
    if (includeTextureCoordinates){
        meshBuilder.withUVs(finalTextureCoordinates);
    }
    if (includeNormals){
        meshBuilder.withNormals(finalNormals);
    }

    for (int i=0;i<indices.size();i++){
        outModelMaterials.push_back(createMaterial(indices[i].materialName, materials, path));
        meshBuilder.withIndices(indices[i].vertexIndices, MeshTopology::Triangles, i);
    }


    return meshBuilder.build();
}

