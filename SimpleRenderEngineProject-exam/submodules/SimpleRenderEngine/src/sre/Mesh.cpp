/*
 *  SimpleRenderEngine (https://github.com/mortennobel/SimpleRenderEngine)
 *
 *  Created by Morten Nobel-Jørgensen ( http://www.nobel-joergensen.com/ )
 *  License: MIT
 */

#include "sre/Mesh.hpp"

#include <algorithm>
#include "sre/impl/GL.hpp"
#include <glm/gtc/constants.hpp>
#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <iomanip>
#include <sstream>
#include "sre/Renderer.hpp"
#include "sre/Shader.hpp"
#include "sre/Log.hpp"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

namespace sre {
    uint16_t Mesh::meshIdCount = 0;

    Mesh::Mesh(std::map<std::string,std::vector<float>>&& attributesFloat,std::map<std::string,std::vector<glm::vec2>>&& attributesVec2, std::map<std::string,std::vector<glm::vec3>>&& attributesVec3,std::map<std::string,std::vector<glm::vec4>>&& attributesVec4,std::map<std::string,std::vector<glm::ivec4>>&& attributesIVec4, std::vector<std::vector<uint32_t>> &&indices, std::vector<MeshTopology> meshTopology, std::string name,RenderStats& renderStats)
    {
        meshId = meshIdCount++;
        if ( Renderer::instance == nullptr){
            LOG_FATAL("Cannot instantiate sre::Mesh before sre::Renderer is created.");
        }
        glGenBuffers(1, &vertexBufferId);
        update(std::move(attributesFloat),
               std::move(attributesVec2),
               std::move(attributesVec3),
               std::move(attributesVec4),
               std::move(attributesIVec4),
               std::move(indices),
               meshTopology,
               name,
               renderStats);
        Renderer::instance->meshes.emplace_back(this);
    }

    Mesh::~Mesh(){
        auto r = Renderer::instance;
        if (r != nullptr){
            RenderStats& renderStats = r->renderStats;
            auto datasize = getDataSize();
            renderStats.meshBytes -= datasize;
            renderStats.meshBytesDeallocated += datasize;
            renderStats.meshCount--;
            r->meshes.erase(std::remove(r->meshes.begin(), r->meshes.end(), this));
        

            if (renderInfo().graphicsAPIVersionMajor >= 3) {
                for (auto arrayObj : shaderToVertexArrayObject) {
                    glDeleteVertexArrays(1, &(arrayObj.second.vaoID));
                }
            }
            glDeleteBuffers(1, &vertexBufferId);
            if (elementBufferId != 0){
                glDeleteBuffers(1, &elementBufferId);
            }
        }
    }

    void Mesh::bind(Shader* shader) {
        if (renderInfo().graphicsAPIVersionMajor >= 3) {
            auto res = shaderToVertexArrayObject.find(shader->shaderProgramId);
            if (res != shaderToVertexArrayObject.end() && res->second.shaderId == shader->shaderUniqueId) {
                GLuint vao = res->second.vaoID;
                glBindVertexArray(vao);
            } else {
                GLuint index;
                if (res != shaderToVertexArrayObject.end()){
                    index = res->second.vaoID;
                } else {
                    glGenVertexArrays(1, &index);
                }
                glBindVertexArray(index);
                setVertexAttributePointers(shader);
                shaderToVertexArrayObject[shader->shaderProgramId] = {shader->shaderUniqueId, index};
                bindIndexSet();
            }
        } else {
            setVertexAttributePointers(shader);
            bindIndexSet();
        }
    }
    void Mesh::bindIndexSet(){
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferId);
    }

    MeshTopology Mesh::getMeshTopology(int indexSet) {
        return meshTopology[indexSet];
    }

    int Mesh::getVertexCount() {
        return vertexCount;
    }

    void Mesh::update(std::map<std::string,std::vector<float>>&& attributesFloat,std::map<std::string,std::vector<glm::vec2>>&& attributesVec2, std::map<std::string,std::vector<glm::vec3>>&& attributesVec3,std::map<std::string,std::vector<glm::vec4>>&& attributesVec4,std::map<std::string,std::vector<glm::ivec4>>&& attributesIVec4, std::vector<std::vector<uint32_t>> &&indices, std::vector<MeshTopology> meshTopology,std::string name,RenderStats& renderStats) {
        this->meshTopology = meshTopology;
        this->name = name;
        meshId = meshIdCount++;

        vertexCount = 0;
        dataSize = 0;

        if (renderInfo().graphicsAPIVersionMajor >= 3) {
            for (auto arrayObj : shaderToVertexArrayObject){
                glDeleteVertexArrays(1, &(arrayObj.second.vaoID));
            }
            shaderToVertexArrayObject.clear();
        }
        attributeByName.clear();

        this->indices         = std::move(indices);
        this->attributesFloat = std::move(attributesFloat);
        this->attributesVec2  = std::move(attributesVec2);
        this->attributesVec3  = std::move(attributesVec3);
        this->attributesVec4  = std::move(attributesVec4);
        this->attributesIVec4 = std::move(attributesIVec4);

        auto interleavedData = getInterleavedData();

        if (renderInfo().graphicsAPIVersionMajor >= 3) {
            glBindVertexArray(0);
        }
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float)*interleavedData.size(), interleavedData.data(), GL_STATIC_DRAW);

        updateIndexBuffers();

        boundsMinMax[0] = glm::vec3{std::numeric_limits<float>::max()};
        boundsMinMax[1] = glm::vec3{-std::numeric_limits<float>::max()};
        auto pos = this->attributesVec3.find("position");
        if (pos != this->attributesVec3.end()){
            for (auto v : pos->second){
                boundsMinMax[0] = glm::min(boundsMinMax[0], v);
                boundsMinMax[1] = glm::max(boundsMinMax[1], v);
            }
        }
        dataSize = totalBytesPerVertex * vertexCount;

        renderStats.meshBytes += dataSize;
        renderStats.meshBytesAllocated += dataSize;
    }

    void Mesh::updateIndexBuffers() {
        elementBufferOffsetCount.clear();
        if (this->indices.empty()){
            if (elementBufferId != 0){
                glDeleteBuffers(1, &elementBufferId);
                elementBufferId = 0;
            }
        } else if (this->indices.size()>0){
            if (elementBufferId == 0){
                glGenBuffers(1, &elementBufferId);
            }
            uint32_t offset = 0;
            for (int i=0;i<this->indices.size();i++) {
                auto & idx = this->indices[i];
                int indexSize;
                uint32_t type;
                if (vertexCount < std::numeric_limits<uint16_t>().max()){
                    indexSize = sizeof(uint16_t)*idx.size();
                    type = GL_UNSIGNED_SHORT;
                } else {
                    uint32_t maxElem = *std::max_element(idx.begin(), idx.end());
                    if (maxElem <= std::numeric_limits<uint16_t>().max()){
                        indexSize = sizeof(uint16_t)*idx.size();
                        type = GL_UNSIGNED_SHORT;
                    } else {
                        indexSize = sizeof(uint32_t)*idx.size();
                        type = GL_UNSIGNED_INT;
                        // enforce alignment to 4 bytes
                        if (offset%4==2){
                            offset+=2;
                        }
                    }
                }

                elementBufferOffsetCount.push_back({offset, (uint32_t)this->indices[i].size(), type});
                offset += indexSize;
            }
            std::vector<uint8_t> concatenatedIndices;
            concatenatedIndices.reserve(offset);

            for (int i=0;i<this->indices.size();i++) {
                uint8_t* dest = concatenatedIndices.data()+elementBufferOffsetCount[i].offset;
                if (elementBufferOffsetCount[i].type == GL_UNSIGNED_INT){
                    void* srcData = this->indices[i].data();
                    memcpy( dest,srcData, this->indices[i].size() * sizeof(uint32_t));
                } else {
                    uint16_t* dest16 = reinterpret_cast<uint16_t *>(dest);
                    for (int j=0;j<this->indices[i].size();j++){
                        dest16[j] = static_cast<uint16_t>(this->indices[i][j]);
                    }
                }
            }
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferId);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, offset, concatenatedIndices.data(), GL_STATIC_DRAW);

            this->dataSize += offset;
        }
    }

    void Mesh::setVertexAttributePointers(Shader* shader) {
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
        int vertexAttribArray = 0;
        for (auto shaderAttribute : shader->attributes) {
            auto meshAttribute = attributeByName.find(shaderAttribute.first);

            bool attributeFoundInMesh = meshAttribute != attributeByName.end();
            // allows mesh attributes to be smaller than shader attributes. E.g. if mesh is Vec2 and shader is Vec4, then OpenGL automatically append (z = 0.0, w=1.0) to the attribute in the shader
            // currently only supported from vec2 or vec3 (not float)
            // todo - add support float - vecX
            bool equalType = attributeFoundInMesh && (shaderAttribute.second.type == meshAttribute->second.attributeType ||
                    (shaderAttribute.second.type >= GL_FLOAT_VEC2 && shaderAttribute.second.type <= GL_FLOAT_VEC4 && shaderAttribute.second.type>= meshAttribute->second.attributeType)
                    || (shaderAttribute.second.type >= GL_INT_VEC2 && shaderAttribute.second.type <= GL_INT_VEC4 && shaderAttribute.second.type>= meshAttribute->second.attributeType)
                                                     );
            if (attributeFoundInMesh &&  equalType && shaderAttribute.second.arraySize == 1) {
				glEnableVertexAttribArray(shaderAttribute.second.position);
                if ((shaderAttribute.second.type >= GL_INT_VEC2 && shaderAttribute.second.type <= GL_INT_VEC4 && shaderAttribute.second.type>= meshAttribute->second.attributeType)){
                    glVertexAttribIPointer(shaderAttribute.second.position, meshAttribute->second.elementCount, meshAttribute->second.dataType, totalBytesPerVertex, BUFFER_OFFSET(meshAttribute->second.offset));
                } else {
                    glVertexAttribPointer(shaderAttribute.second.position, meshAttribute->second.elementCount, meshAttribute->second.dataType, GL_FALSE, totalBytesPerVertex, BUFFER_OFFSET(meshAttribute->second.offset));
                }
                vertexAttribArray++;
            } else {
				assert(shaderAttribute.second.arraySize == 1 && "Constant vertex attributes not supported as arrays");
				glDisableVertexAttribArray(shaderAttribute.second.position);
				static const float a[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
                switch (shaderAttribute.second.type) {
				case GL_INT_VEC4:
					glVertexAttribI4iv(shaderAttribute.second.position, (GLint*)a);
					break;
				case GL_FLOAT_VEC4:
					glVertexAttrib4fv(shaderAttribute.second.position, a);
					break;
				case GL_FLOAT_VEC3:
					glVertexAttrib3fv(shaderAttribute.second.position, a);
					break;
				case GL_FLOAT_VEC2:
					glVertexAttrib2fv(shaderAttribute.second.position, a);
					break;
				case GL_FLOAT:
					glVertexAttrib1fv(shaderAttribute.second.position, a);
					break;
                default:
                    LOG_ERROR("Unhandled attribute type: %i",(int)shaderAttribute.second.type);
                	break;

                }
            }
        }
    }

    std::vector<glm::vec3> Mesh::getPositions() {
        std::vector<glm::vec3> res;
        auto ref = attributesVec3.find("position");
        if (ref != attributesVec3.end()){
            res = ref->second;
        }
        return res;
    }

    std::vector<glm::vec3> Mesh::getNormals() {
        std::vector<glm::vec3> res;
        auto ref = attributesVec3.find("normal");
        if (ref != attributesVec3.end()){
            res = ref->second;
        }
        return res;
    }

    std::vector<glm::vec4> Mesh::getUVs() {
        std::vector<glm::vec4> res;
        auto ref = attributesVec4.find("uv");
        if (ref != attributesVec4.end()){
            res = ref->second;
        }
        return res;
    }

    const std::vector<uint32_t>& Mesh::getIndices(int indexSet) {
        return indices.at(indexSet);
    }

    Mesh::MeshBuilder Mesh::update() {
        Mesh::MeshBuilder res;
        res.updateMesh = this;

        res.attributesFloat = attributesFloat;
        res.attributesVec2 = attributesVec2;
        res.attributesVec3 = attributesVec3;
        res.attributesVec4 = attributesVec4;
        res.attributesIVec4 = attributesIVec4;

        res.indices = indices;
        res.meshTopology = meshTopology;
        return res;
    }

    Mesh::MeshBuilder Mesh::create() {
        return Mesh::MeshBuilder();
    }

    std::vector<glm::vec4> Mesh::getColors() {
        std::vector<glm::vec4> res;
        auto ref = attributesVec4.find("color");
        if (ref != attributesVec4.end()){
            res = ref->second;
        }
        return res;
    }

    std::vector<float> Mesh::getParticleSizes() {
        std::vector<float> res;
        auto ref = attributesFloat.find("particleSize");
        if (ref != attributesFloat.end()){
            res = ref->second;
        }
        return res;
    }

    int Mesh::getDataSize() {
        return dataSize;
    }

    std::array<glm::vec3,2> Mesh::getBoundsMinMax() {
        return boundsMinMax;
    }

    std::pair<int,int> Mesh::getType(const std::string &name) {
        auto res = attributeByName.find(name);
        if (res != attributeByName.end()){
            return {res->second.dataType,res->second.elementCount};
        }
        return {-1,-1};
    }

    std::vector<std::string> Mesh::getAttributeNames() {
        std::vector<std::string> res;
        for (auto & u : attributeByName){
            res.push_back(u.first);
        }
        return res;
    }

    int Mesh::getIndexSets() {
        return indices.size();
    }

    const std::string& Mesh::getName() {
        return name;
    }

    int Mesh::getIndicesSize(int indexSet) {
        if (indexSet < indices.size()) {
            return static_cast<int>(indices[indexSet].size());
        }
        LOG_ERROR("Indexset %i out of bounds.",indexSet);
        return -1;
    }

    std::vector<glm::vec4> Mesh::getTangents() {
        std::vector<glm::vec4> res;
        auto ref = attributesVec4.find("tangent");
        if (ref != attributesVec4.end()){
            res = ref->second;
        }
        return res;
    }

    std::vector<float> Mesh::getInterleavedData() {
        totalBytesPerVertex = 0;
        std::vector<int> offset;
        // enforced std140 layout rules ( https://learnopengl.com/#!Advanced-OpenGL/Advanced-GLSL )
        // the order is vec3, vec4, ivec4, vec2, float
        for (auto & pair : attributesVec3){
            vertexCount = std::max(vertexCount, (int)pair.second.size());
            offset.push_back(totalBytesPerVertex);
            attributeByName[pair.first] = {totalBytesPerVertex, 3, GL_FLOAT, GL_FLOAT_VEC3};
            totalBytesPerVertex += sizeof(glm::vec4); // note use vec4 size
        }
        for (auto & pair : attributesVec4){
            vertexCount = std::max(vertexCount, (int)pair.second.size());
            offset.push_back(totalBytesPerVertex);
            attributeByName[pair.first] = {totalBytesPerVertex, 4, GL_FLOAT, GL_FLOAT_VEC4};
            totalBytesPerVertex += sizeof(glm::vec4);
        }
        for (auto & pair : attributesIVec4){
            vertexCount = std::max(vertexCount, (int)pair.second.size());
            offset.push_back(totalBytesPerVertex);
            attributeByName[pair.first] = {totalBytesPerVertex, 4,GL_INT, GL_INT_VEC4};
            totalBytesPerVertex += sizeof(glm::i32vec4);
        }
        for (auto & pair : attributesVec2){
            vertexCount = std::max(vertexCount, (int)pair.second.size());
            offset.push_back(totalBytesPerVertex);
            attributeByName[pair.first] = {totalBytesPerVertex, 2, GL_FLOAT,GL_FLOAT_VEC2};
            totalBytesPerVertex += sizeof(glm::vec2);
        }
        for (auto & pair : attributesFloat){
            vertexCount = std::max(vertexCount, (int)pair.second.size());
            offset.push_back(totalBytesPerVertex);
            attributeByName[pair.first] = {totalBytesPerVertex, 1, GL_FLOAT, GL_FLOAT};
            totalBytesPerVertex += sizeof(float);
        }
        // add final padding (make vertex align with vec4)
        if (totalBytesPerVertex%(sizeof(float)*4) != 0) {
            totalBytesPerVertex += sizeof(float)*4 - totalBytesPerVertex%(sizeof(float)*4);
        }
        std::vector<float> interleavedData((vertexCount * totalBytesPerVertex) / sizeof(float), 0);
        const char * dataPtr = (char*) interleavedData.data();

        // add data (copy each element into interleaved buffer)
        for (auto & pair : attributesVec3){
            auto& offsetBytes = attributeByName[pair.first];
            for (int i=0;i<pair.second.size();i++){
                glm::vec3 * locationPtr = (glm::vec3 *) (dataPtr + (totalBytesPerVertex * i) + offsetBytes.offset);
                *locationPtr = pair.second[i];
            }
        }
        for (auto & pair : attributesVec4){
            auto& offsetBytes = attributeByName[pair.first];
            for (int i=0;i<pair.second.size();i++) {
                glm::vec4 * locationPtr = (glm::vec4 *) (dataPtr + totalBytesPerVertex * i + offsetBytes.offset);
                *locationPtr = pair.second[i];
            }
        }
        for (auto & pair : attributesIVec4){
            auto& offsetBytes = attributeByName[pair.first];
            for (int i=0;i<pair.second.size();i++) {
                glm::i32vec4 * locationPtr = (glm::i32vec4 *) (dataPtr + totalBytesPerVertex * i + offsetBytes.offset);
                *locationPtr = pair.second[i];
            }
        }
        for (auto & pair : attributesVec2){
            auto& offsetBytes = attributeByName[pair.first];
            for (int i=0;i<pair.second.size();i++) {
                glm::vec2 * locationPtr = (glm::vec2 *) (dataPtr + totalBytesPerVertex * i + offsetBytes.offset);
                *locationPtr = pair.second[i];
            }
        }
        for (auto & pair : attributesFloat){
            auto& offsetBytes = attributeByName[pair.first];
            for (int i=0;i<pair.second.size();i++) {
                float * locationPtr = (float *) (dataPtr + totalBytesPerVertex * i + offsetBytes.offset);
                *locationPtr = pair.second[i];
            }
        }
        return interleavedData;
    }

    void Mesh::setBoundsMinMax(const std::array<glm::vec3,2>& minMax) {
        boundsMinMax = minMax;
    }

    bool Mesh::hasAttribute(std::string name) {
        return attributeByName.find(name) != attributeByName.end();
    }

    Mesh::MeshBuilder &Mesh::MeshBuilder::withPositions(const std::vector<glm::vec3> &vertexPositions) {
        withAttribute("position", vertexPositions);
        return *this;
    }

    Mesh::MeshBuilder &Mesh::MeshBuilder::withNormals(const std::vector<glm::vec3> &normals) {
        withAttribute("normal", normals);
        return *this;
    }

    Mesh::MeshBuilder &Mesh::MeshBuilder::withUVs(const std::vector<glm::vec4> &uvs) {
        withAttribute("uv", uvs);
        return *this;
    }

    Mesh::MeshBuilder &Mesh::MeshBuilder::withColors(const std::vector<glm::vec4> &colors) {
        withAttribute("vertex_color", colors);
        return *this;
    }

    Mesh::MeshBuilder &Mesh::MeshBuilder::withTangents(const std::vector<glm::vec4> &tangent) {
        withAttribute("tangent", tangent);
        return *this;
    }

    Mesh::MeshBuilder &Mesh::MeshBuilder::withParticleSizes(const std::vector<float> &particleSize) {
        withAttribute("particleSize", particleSize);
        return *this;
    }

    Mesh::MeshBuilder &Mesh::MeshBuilder::withMeshTopology(MeshTopology meshTopology) {
        if (this->meshTopology.empty()){
            this->meshTopology.emplace_back();
        }
        this->meshTopology[0] = meshTopology;
        return *this;
    }

    Mesh::MeshBuilder &Mesh::MeshBuilder::withIndices(const std::vector<uint16_t> &indices,MeshTopology meshTopology, int indexSet) {
        std::vector<uint32_t> indices32(indices.size());
        for (int i=0;i<indices32.size();i++){
            indices32[i] = indices[i];
        }

        return withIndices(indices32, meshTopology, indexSet);
    }

    Mesh::MeshBuilder &Mesh::MeshBuilder::withIndices(const std::vector<uint32_t> &indices,MeshTopology meshTopology, int indexSet) {
        while (indexSet >= this->indices.size()){
            this->indices.emplace_back();
        }
        while (indexSet >= this->meshTopology.size()){
            this->meshTopology.emplace_back();
        }

        this->indices[indexSet] = indices;
        this->meshTopology[indexSet] = meshTopology;
        return *this;
    }

    std::vector<glm::vec4> Mesh::MeshBuilder::computeTangents(const std::vector<glm::vec3>& normals){
        if (attributesVec3.find("position") == attributesVec3.end()){
            LOG_WARNING("Cannot find vertex attribute position (vec3) required for recomputeNormals()");
            return {};
        }
        if (attributesVec4.find("uv") == attributesVec4.end()){
            LOG_WARNING("Cannot find vertex attribute uv (vec4) required for recomputeNormals()");
            return {};
        }

        std::vector<glm::vec3> vertexPositions = attributesVec3["position"];
        std::vector<glm::vec4> uvs = attributesVec4["uv"];

        std::vector<glm::vec3> tan1(vertexPositions.size(), glm::vec3(0.0f));
        std::vector<glm::vec3> tan2(vertexPositions.size(), glm::vec3(0.0f));

        auto computeTangent = [&](int i1, int i2, int i3) {
            auto v1 = vertexPositions[i1];
            auto v2 = vertexPositions[i2];
            auto v3 = vertexPositions[i3];

            auto w1 = glm::vec2(uvs[i1]);
            auto w2 = glm::vec2(uvs[i2]);
            auto w3 = glm::vec2(uvs[i3]);

            float x1 = v2.x - v1.x;
            float x2 = v3.x - v1.x;
            float y1 = v2.y - v1.y;
            float y2 = v3.y - v1.y;
            float z1 = v2.z - v1.z;
            float z2 = v3.z - v1.z;

            float s1 = w2.x - w1.x;
            float s2 = w3.x - w1.x;
            float t1 = w2.y - w1.y;
            float t2 = w3.y - w1.y;

            float r = 1.0F / (s1 * t2 - s2 * t1);
            glm::vec3 sdir((t2 * x1 - t1 * x2) * r, (t2 * y1 - t1 * y2) * r,
                          (t2 * z1 - t1 * z2) * r);
            glm::vec3 tdir((s1 * x2 - s2 * x1) * r, (s1 * y2 - s2 * y1) * r,
                          (s1 * z2 - s2 * z1) * r);

            tan1[i1] += sdir;
            tan1[i2] += sdir;
            tan1[i3] += sdir;

            tan2[i1] += tdir;
            tan2[i2] += tdir;
            tan2[i3] += tdir;
        };

        if (indices.empty()){
            if (meshTopology[0] != MeshTopology::Triangles){
                LOG_WARNING("Cannot only triangles supported for recomputeTangents()");
                return {};
            }
            for (int i=0;i<vertexPositions.size();i=i+3){
                computeTangent(i, i+1, i+2);
            }
        } else {
            for (int j=0;j<indices.size();j++){
                if (meshTopology[j] != MeshTopology::Triangles){
                    LOG_WARNING("Cannot only triangles supported for recomputeTangents()");
                    return {};
                }
                auto & submeshIdx = indices[j];
                for (int i=0;i<submeshIdx.size();i=i+3){
                    computeTangent(submeshIdx[i], submeshIdx[i+1], submeshIdx[i+2]);
                }
            }
        }

        std::vector<glm::vec4> tangent(vertexPositions.size());
        for (long a = 0; a < vertexPositions.size(); a++)
        {
            auto n = normals[a];
            auto t = tan1[a];

            tangent[a] = glm::vec4(
                    // Gram-Schmidt orthogonalize
                    glm::normalize(t - n * glm::dot(n, t)),
                    // Calculate handedness
                    (glm::dot(glm::cross(n, t), tan2[a]) < 0.0F) ? -1.0F : 1.0F);
        }
        return tangent;
    }

    std::vector<glm::vec3> Mesh::MeshBuilder::computeNormals(){
        if (attributesVec3.find("position") == attributesVec3.end()){
            LOG_WARNING("Cannot find vertex attribute position (vec3) for recomputeNormals()");
            return {};
        }

        std::vector<glm::vec3> vertexPositions = attributesVec3["position"];
        std::vector<glm::vec3> normals(vertexPositions.size(), glm::vec3(0));

        auto computeNormal = [&](int i1, int i2, int i3){
            auto v1 = vertexPositions[i1];
            auto v2 = vertexPositions[i2];
            auto v3 = vertexPositions[i3];
            auto v1v2 = glm::normalize(v2 - v1);
            auto v1v3 = glm::normalize(v3 - v1);
            auto normal = glm::normalize(glm::cross(v1v2, v1v3));
            float weight1 = acos(glm::max(-1.0f, glm::min(1.0f, glm::dot(v1v2, v1v3))));
            auto v2v3Alias = glm::normalize(v3 - v2);
            float weight2 = glm::pi<float>() - acos(glm::max(-1.0f, glm::min(1.0f, glm::dot(v1v2, v2v3Alias))));
            normals[i1] += normal * weight1;
            normals[i2] += normal * weight2;
            normals[i3] += normal * (glm::pi<float>() - weight1 - weight2);
        };

        if (indices.empty()){
            if (meshTopology[0] != MeshTopology::Triangles){
                LOG_WARNING("Cannot only triangles supported for recomputeNormals()");
                return {};
            }
            for (int i=0;i<vertexPositions.size();i=i+3){
                computeNormal(i, i+1, i+2);
            }
        } else {
            for (int j=0;j<indices.size();j++){
                if (meshTopology[j] != MeshTopology::Triangles){
                    LOG_WARNING("Cannot only triangles supported for recomputeNormals()");
                    return {};
                }
                auto & submeshIdx = indices[j];
                for (int i=0;i<submeshIdx.size();i=i+3){
                    computeNormal(submeshIdx[i], submeshIdx[i+1], submeshIdx[i+2]);
                }
            }
        }

        for (auto & val : normals){
            val = glm::normalize(val);
        }
        return normals;
    }

    std::shared_ptr<Mesh> Mesh::MeshBuilder::build() {
        // update stats
        RenderStats& renderStats = Renderer::instance->renderStats;

        if (name.length()==0){
            name = "Unnamed Mesh";
        }

        if (recomputeNormals){
            auto newNormals = computeNormals();
            if (!newNormals.empty()){
                withNormals(newNormals);
            }
        }

        if (recomputeTangents){
            bool hasNormals = attributesVec3.find("normal") == attributesVec3.end();
            auto newTangents = computeTangents(hasNormals ? attributesVec3["normal"] : computeNormals());
            if (!newTangents.empty()){
                withTangents(newTangents);
            }
        }
        if (updateMesh != nullptr){
            renderStats.meshBytes -= updateMesh->getDataSize();
            updateMesh->update(std::move(this->attributesFloat), std::move(this->attributesVec2), std::move(this->attributesVec3), std::move(this->attributesVec4), std::move(this->attributesIVec4), std::move(indices), meshTopology,name,renderStats);


            return updateMesh->shared_from_this();
        }

        auto res = new Mesh(std::move(this->attributesFloat), std::move(this->attributesVec2), std::move(this->attributesVec3), std::move(this->attributesVec4), std::move(this->attributesIVec4), std::move(indices),meshTopology,name,renderStats);
        renderStats.meshCount++;

        return std::shared_ptr<Mesh>(res);

    }

    Mesh::MeshBuilder &Mesh::MeshBuilder::withSphere(int stacks, int slices, float radius) {
        using namespace glm;
        using namespace std;

        if (name.length() == 0){
            std::stringstream ss;
            ss <<"SRE Sphere "<< stacks<<"-"<<slices<<"-"<<std::setprecision( 2 ) <<radius;
            name = ss.str();
        }

        size_t vertexCount = (size_t) ((stacks + 1) * (slices+1));
        vector<vec3> vertices{vertexCount};
        vector<vec3> normals{vertexCount};
        vector<vec4> tangents{vertexCount};
        vector<vec4> uvs{vertexCount};

        int index = 0;
        // create vertices
        for (unsigned short j = 0; j <= stacks; j++) {
            double latitude1 = (glm::pi<double>() / stacks) * j - (glm::pi<double>() / 2);
            double sinLat1 = sin(latitude1);
            double cosLat1 = cos(latitude1);
            for (int i = 0; i <= slices; i++) {
                double longitude = ((glm::pi<double>() * 2) / slices) * i;
                double sinLong = sin(longitude);
                double cosLong = cos(longitude);
                dvec3 normalD{cosLong * cosLat1,
                            sinLat1,
                            sinLong * cosLat1};
                vec3 normal = (vec3)normalize(normalD);
                vec4 tangent = vec4((vec3)normalize(dvec3(cos(longitude+glm::half_pi<double>()),0, sin(longitude+glm::half_pi<double>()))),1);
                normals[index] = normal;
                tangents[index] = tangent;
                uvs[index] = vec4{1 - i /(float) slices, j /(float) stacks,0,0};
                vertices[index] = normal * radius;
                index++;
            }
        }
        vector<vec3> finalPosition;
        vector<vec3> finalNormals;
        vector<vec4> finalTangents;
        vector<vec4> finalUVs;
        // create indices
        for (int j = 0; j < stacks; j++) {
            for (int i = 0; i <= slices; i++) {
                glm::u8vec2 offset [] = {
                        // first triangle
                        glm::u8vec2{i,j},
                        glm::u8vec2{(i+1)%(slices+1),j+1},
                        glm::u8vec2{(i+1)%(slices+1),j},

                        // second triangle
                        glm::u8vec2{i,j},
                        glm::u8vec2{i,j+1},
                        glm::u8vec2{(i+1)%(slices+1),j+1},

                };
                for (auto o : offset){
                    index = o[1] * (slices+1)  + o[0];
                    finalPosition.push_back(vertices[index]);
                    finalNormals.push_back(normals[index]);
                    finalTangents.push_back(tangents[index]);
                    finalUVs.push_back(uvs[index]);
                }

            }
        }

        withPositions(finalPosition);
        withNormals(finalNormals);
        withTangents(finalTangents);
        withUVs(finalUVs);
        withMeshTopology(MeshTopology::Triangles);

        return *this;
    }

    Mesh::MeshBuilder &Mesh::MeshBuilder::withTorus(int segmentsC, int segmentsA, float radiusC, float radiusA) {
        using namespace glm;
        using namespace std;

        //  losely based on http://mathworld.wolfram.com/Torus.html
        if (name.length() == 0){
            std::stringstream ss;
            ss <<"SRE Torus "<< segmentsC<<"-"<<segmentsA<<"-"<<std::setprecision( 2 ) <<radiusC<<"-"<<radiusA;
            name = ss.str();
        }

        size_t vertexCount = (size_t) ((segmentsC + 1) * (segmentsA+1));
        vector<vec3> vertices{vertexCount};
        vector<vec3> normals{vertexCount};
        vector<vec4> tangents{vertexCount};
        vector<vec4> uvs{vertexCount};

        int index = 0;

        // create vertices
        for (unsigned short j = 0; j <= segmentsC; j++) {
            // outer circle
            float u = glm::two_pi<float>() * j/(float)segmentsC;
            auto t = vec4((vec3)normalize(dvec3(cos(u+glm::half_pi<double>()),sin(u+glm::half_pi<double>()),0)),1);
            for (int i = 0; i <= segmentsA; i++) {
                // inner circle
                float v = glm::two_pi<float>() * i/(float)segmentsA;
                glm::vec3 pos {
                        (radiusC+radiusA*cos(v))*cos(u),
                        (radiusC+radiusA*cos(v))*sin(u),
                        radiusA*sin(v)
                };
                glm::vec3 posOuter {
                        (radiusC+(radiusA*2)*cos(v))*cos(u),
                        (radiusC+(radiusA*2)*cos(v))*sin(u),
                        (radiusA*2)*sin(v)
                };
                glm::vec3 tangent {
                        (radiusC+radiusA*cos(v))*cos(u),
                        (radiusC+radiusA*cos(v))*sin(u),
                        radiusA*sin(v)
                };
                uvs[index] = vec4{1 - j /(float) segmentsC, i /(float) segmentsA,0,0};
                vertices[index] = pos;
                normals[index] = glm::normalize(posOuter - pos);
                tangents[index] = t;
                index++;
            }
        }
        vector<vec3> finalPosition;
        vector<vec3> finalNormals;
        vector<vec4> finalTangents;
        vector<vec4> finalUVs;
        // create indices
        for (int j = 0; j < segmentsC; j++) {
            for (int i = 0; i <= segmentsA; i++) {
                glm::u8vec2 offset [] = {
                        // first triangle
                        glm::u8vec2{i,j},
                        glm::u8vec2{(i+1)%(segmentsA+1),j+1},
                        glm::u8vec2{(i+1)%(segmentsA+1),j},

                        // second triangle
                        glm::u8vec2{i,j},
                        glm::u8vec2{i,j+1},
                        glm::u8vec2{(i+1)%(segmentsA+1),j+1},

                };
                for (auto o : offset){
                    index = o[1] * (segmentsA+1)  + o[0];
                    finalPosition.push_back(vertices[index]);
                    finalNormals.push_back(normals[index]);
                    finalTangents.push_back(tangents[index]);
                    finalUVs.push_back(uvs[index]);
                }

            }
        }

        withPositions(finalPosition);
        withNormals(finalNormals);
        withTangents(finalTangents);
        withUVs(finalUVs);
        withMeshTopology(MeshTopology::Triangles);

        return *this;
    }

    Mesh::MeshBuilder &Mesh::MeshBuilder::withCube(float length) {
        using namespace glm;
        using namespace std;

        if (name.length() == 0){
            std::stringstream ss;
            ss <<"SRE Cube "<<std::setprecision( 2 ) <<length;
            name = ss.str();
        }


        //    v5----- v4
        //   /|      /|
        //  v1------v0|
        //  | |     | |
        //  | |v6---|-|v7
        //  |/      |/
        //  v2------v3
        vec3 p[] = {
                vec3{length, length, length},
                vec3{-length, length, length},
                vec3{-length, -length, length},
                vec3{length, -length, length},

                vec3{length, length, -length},
                vec3{-length, length, -length},
                vec3{-length, -length, -length},
                vec3{length, -length, -length}

        };
        vector<uint32_t> indices({
                                    0,1,2, 0,2,3,
                                    4,5,6, 4,6,7,
                                    8,9,10, 8,10,11,
                                    12,13,14, 12, 14,15,
                                    16,17,18, 16,18,19,
                                    20,21,22, 20,22,23
                                 });
        vector<vec3> positions({p[0],p[1],p[2], p[3], // v0-v1-v2-v3
                                p[4],p[0],p[3], p[7], // v4-v0-v3-v7
                                p[5],p[4],p[7], p[6], // v5-v4-v7-v6
                                p[1],p[5],p[6], p[2], // v1-v5-v6-v2
                                p[4],p[5],p[1], p[0], // v1-v5-v6-v2
                                p[3],p[2],p[6], p[7], // v1-v5-v6-v2
                               });
        vec4 u[] = {
                vec4(1,1,0,0),
                vec4(0,1,0,0),
                vec4(0,0,0,0),
                vec4(1,0,0,0)
        };
        vector<vec4> uvs({ u[0],u[1],u[2], u[3],
                           u[0],u[1],u[2], u[3],
                           u[0],u[1],u[2], u[3],
                           u[0],u[1],u[2], u[3],
                           u[0],u[1],u[2], u[3],
                           u[0],u[1],u[2], u[3],
                         });
        vector<vec3> normals({
                                     vec3{0, 0, 1},
                                     vec3{0, 0, 1},
                                     vec3{0, 0, 1},
                                     vec3{0, 0, 1},
                                     vec3{1, 0, 0},
                                     vec3{1, 0, 0},
                                     vec3{1, 0, 0},
                                     vec3{1, 0, 0},
                                     vec3{0, 0, -1},
                                     vec3{0, 0, -1},
                                     vec3{0, 0, -1},
                                     vec3{0, 0, -1},
                                     vec3{-1, 0, 0},
                                     vec3{-1, 0, 0},
                                     vec3{-1, 0, 0},
                                     vec3{-1, 0, 0},
                                     vec3{0, 1, 0},
                                     vec3{0, 1, 0},
                                     vec3{0, 1, 0},
                                     vec3{0, 1, 0},
                                     vec3{0, -1, 0},
                                     vec3{0, -1, 0},
                                     vec3{0, -1, 0},
                                     vec3{0, -1, 0},
                             });

        vector<vec4> tangents({
                                     vec4{1, 0,  0,1},
                                     vec4{1, 0,  0,1},
                                     vec4{1, 0,  0,1},
                                     vec4{1, 0,  0,1},
                                     vec4{0, 0, -1,1},
                                     vec4{0, 0, -1,1},
                                     vec4{0, 0, -1,1},
                                     vec4{0, 0, -1,1},
                                     vec4{-1, 0, 0,1},
                                     vec4{-1, 0, 0,1},
                                     vec4{-1, 0, 0,1},
                                     vec4{-1, 0, 0,1},
                                     vec4{0, 0,  1,1},
                                     vec4{0, 0,  1,1},
                                     vec4{0, 0,  1,1},
                                     vec4{0, 0,  1,1},
                                     vec4{1, 0,  0,1},
                                     vec4{1, 0,  0,1},
                                     vec4{1, 0,  0,1},
                                     vec4{1, 0,  0,1},
                                     vec4{-1, 0, 0,1},
                                     vec4{-1, 0, 0,1},
                                     vec4{-1, 0, 0,1},
                                     vec4{-1, 0, 0,1},
                             });

        withPositions(positions);
        withNormals(normals);
        withUVs(uvs);
        withTangents(tangents);
        withIndices(indices);
        withMeshTopology(MeshTopology::Triangles);

        return *this;
    }

    Mesh::MeshBuilder &Mesh::MeshBuilder::withQuad(float size) {
        if (name.length() == 0){
            std::stringstream ss;
            ss <<"SRE Quad "<<std::setprecision( 2 ) <<size;
            name = ss.str();
        }

        std::vector<glm::vec3> vertices({
                                                glm::vec3{ size,-size, 0},
                                                glm::vec3{ size, size, 0},
                                                glm::vec3{-size,-size, 0},
                                                glm::vec3{-size, size, 0}
                                        });
        std::vector<glm::vec3> normals({
                                               glm::vec3{0, 0, 1},
                                               glm::vec3{0, 0, 1},
                                               glm::vec3{0, 0, 1},
                                               glm::vec3{0, 0, 1}
                                       });
        std::vector<glm::vec4> tangents({
                                               glm::vec4{1, 0,0, 1},
                                               glm::vec4{1, 0,0, 1},
                                               glm::vec4{1, 0,0, 1},
                                               glm::vec4{1, 0,0, 1}
                                       });
        std::vector<glm::vec4> uvs({
                                           glm::vec4{1, 0,0,0},
                                           glm::vec4{1, 1,0,0},
                                           glm::vec4{0, 0,0,0},
                                           glm::vec4{0, 1,0,0}
                                   });
        std::vector<uint32_t> indices = {
                0,1,2,
                2,1,3
        };
        withPositions(vertices);
        withNormals(normals);
        withTangents(tangents);
        withUVs(uvs);
        withIndices(indices);
        withMeshTopology(MeshTopology::Triangles);

        return *this;
    }

    Mesh::MeshBuilder &Mesh::MeshBuilder::withAttribute(std::string name, const std::vector<float> &values) {
        if (updateMesh != nullptr && attributesFloat.find(name) == attributesFloat.end()){
            LOG_ERROR("Cannot change mesh structure. %s dis not exist in the original mesh as a float.",name.c_str());
        } else {
            attributesFloat[name] = values;
        }
        return *this;
    }

    Mesh::MeshBuilder &Mesh::MeshBuilder::withAttribute(std::string name, const std::vector<glm::vec2> &values) {
        if (updateMesh != nullptr && attributesVec2.find(name) == attributesVec2.end()){
            LOG_ERROR("Cannot change mesh structure. %s dis not exist in the original mesh as a vec2.",name.c_str());
        } else {
            attributesVec2[name] = values;
        }
        return *this;
    }

    Mesh::MeshBuilder &Mesh::MeshBuilder::withAttribute(std::string name, const std::vector<glm::vec3> &values) {
        if (updateMesh != nullptr && attributesVec3.find(name) == attributesVec3.end()){
            LOG_ERROR("Cannot change mesh structure. %s dis not exist in the original mesh as a vec3.",name.c_str());
        } else {
            attributesVec3[name] = values;
        }
        return *this;
    }

    Mesh::MeshBuilder &Mesh::MeshBuilder::withAttribute(std::string name, const std::vector<glm::vec4> &values) {
        if (updateMesh != nullptr && attributesVec4.find(name) == attributesVec4.end()){
            LOG_ERROR("Cannot change mesh structure. %s dis not exist in the original mesh as a vec4.",name.c_str());
        } else {
            attributesVec4[name] = values;
        }
        return *this;
    }

    Mesh::MeshBuilder &Mesh::MeshBuilder::withAttribute(std::string name, const std::vector<glm::ivec4> &values) {
        auto& info = renderInfo();
        if (info.graphicsAPIVersionES && info.graphicsAPIVersionMajor <= 2){
            LOG_INFO("Converting attribute %s to vec4. ES %i Version %i",name.c_str(),info.graphicsAPIVersionES,info.graphicsAPIVersionMajor);
            std::vector<glm::vec4> convertedVec4(values.size(), glm::vec4(0));
            for (int i=0;i<convertedVec4.size();i++){
                convertedVec4[i] = values[i];
            }
            withAttribute(name, convertedVec4);
        }
        else if (updateMesh != nullptr && attributesIVec4.find(name) == attributesIVec4.end()){
            LOG_ERROR("Cannot change mesh structure. %s dis not exist in the original mesh as a ivec4.",name.c_str());
        } else {
            attributesIVec4[name] = values;
        }
        return *this;
    }

    Mesh::MeshBuilder &Mesh::MeshBuilder::withName(const std::string& name) {
        this->name = name;
        return *this;
    }

    Mesh::MeshBuilder& Mesh::MeshBuilder::withRecomputeNormals(bool enabled){
        recomputeNormals = enabled;
        return *this;
    }

    Mesh::MeshBuilder& Mesh::MeshBuilder::withRecomputeTangents(bool enabled){
        recomputeTangents = enabled;
        return *this;
    }
}
