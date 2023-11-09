#!/bin/bash

if [ -z "$EMSDK" ]
then
      echo "\$EMSDK is not defined. Using ~/programming/cpp/emsdk_portable"
      EMSDK=~/programming/cpp/emsdk_portable
fi

source ${EMSDK}/emsdk_env.sh

emcc -Iinclude -Isubmodules/imgui -Isubmodules/glm -Isubmodules/picojson -Isubmodules/ImGuiColorTextEdit \
               submodules/imgui/imgui.cpp \
               submodules/imgui/imgui_draw.cpp \
               submodules/ImGuiColorTextEdit/TextEditor.cpp \
               src/sre/Camera.cpp \
               src/sre/Color.cpp \
               src/sre/Framebuffer.cpp \
               src/sre/imgui_sre.cpp \
               src/sre/Inspector.cpp \
               src/sre/Light.cpp \
               src/sre/Log.cpp \
               src/sre/Material.cpp \
               src/sre/Mesh.cpp \
               src/sre/ModelImporter.cpp \
               src/sre/Renderer.cpp \
               src/sre/RenderPass.cpp \
               src/sre/Resource.cpp \
               src/sre/SDLRenderer.cpp \
               src/sre/Shader.cpp \
               src/sre/Skybox.cpp \
               src/sre/Sprite.cpp \
               src/sre/SpriteAtlas.cpp \
               src/sre/SpriteBatch.cpp \
               src/sre/Texture.cpp \
               src/sre/VR.cpp \
               src/sre/WorldLights.cpp \
               src/sre/impl/GL.cpp \
               src/sre/impl/UniformSet.cpp \
               examples/10_skybox-example.cpp \
               -O2 -std=c++14 -s USE_WEBGL2=1 -s FORCE_FILESYSTEM=1 -s TOTAL_MEMORY=33554432 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' --embed-file examples_data/cube-negx.png --embed-file examples_data/cube-negy.png --embed-file examples_data/cube-negz.png --embed-file examples_data/cube-posx.png --embed-file examples_data/cube-posy.png --embed-file examples_data/cube-posz.png -s USE_SDL=2 -o docs/examples/10_skybox-example.html


emcc -Iinclude -Isubmodules/imgui -Isubmodules/glm -Isubmodules/picojson -Isubmodules/ImGuiColorTextEdit \
               submodules/imgui/imgui.cpp \
               submodules/imgui/imgui_draw.cpp \
               submodules/ImGuiColorTextEdit/TextEditor.cpp \
               src/sre/Camera.cpp \
               src/sre/Color.cpp \
               src/sre/Framebuffer.cpp \
               src/sre/imgui_sre.cpp \
               src/sre/Inspector.cpp \
               src/sre/Light.cpp \
               src/sre/Log.cpp \
               src/sre/Material.cpp \
               src/sre/Mesh.cpp \
               src/sre/ModelImporter.cpp \
               src/sre/Renderer.cpp \
               src/sre/RenderPass.cpp \
               src/sre/Resource.cpp \
               src/sre/SDLRenderer.cpp \
               src/sre/Shader.cpp \
               src/sre/Skybox.cpp \
               src/sre/Sprite.cpp \
               src/sre/SpriteAtlas.cpp \
               src/sre/SpriteBatch.cpp \
               src/sre/Texture.cpp \
               src/sre/VR.cpp \
               src/sre/WorldLights.cpp \
               src/sre/impl/GL.cpp \
               src/sre/impl/UniformSet.cpp \
               examples/12_render-to-texture.cpp \
               -O2 -std=c++14 -s USE_WEBGL2=1 -s FORCE_FILESYSTEM=1 -s TOTAL_MEMORY=33554432 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='[]'  -s USE_SDL=2 -o docs/examples/12_render-to-texture.html

emcc -Iinclude -Isubmodules/imgui -Isubmodules/glm -Isubmodules/picojson -Isubmodules/ImGuiColorTextEdit \
               submodules/imgui/imgui.cpp \
               submodules/imgui/imgui_draw.cpp \
               submodules/ImGuiColorTextEdit/TextEditor.cpp \
               src/sre/Camera.cpp \
               src/sre/Color.cpp \
               src/sre/Framebuffer.cpp \
               src/sre/imgui_sre.cpp \
               src/sre/Inspector.cpp \
               src/sre/Light.cpp \
               src/sre/Log.cpp \
               src/sre/Material.cpp \
               src/sre/Mesh.cpp \
               src/sre/ModelImporter.cpp \
               src/sre/Renderer.cpp \
               src/sre/RenderPass.cpp \
               src/sre/Resource.cpp \
               src/sre/SDLRenderer.cpp \
               src/sre/Shader.cpp \
               src/sre/Skybox.cpp \
               src/sre/Sprite.cpp \
               src/sre/SpriteAtlas.cpp \
               src/sre/SpriteBatch.cpp \
               src/sre/Texture.cpp \
               src/sre/VR.cpp \
               src/sre/WorldLights.cpp \
               src/sre/impl/GL.cpp \
               src/sre/impl/UniformSet.cpp \
               examples/07_matcap.cpp \
               -O2 -std=c++14 -s USE_WEBGL2=1 -s FORCE_FILESYSTEM=1 -s TOTAL_MEMORY=33554432 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' --embed-file examples_data/suzanne.obj --embed-file examples_data/matcap_00001.png --embed-file examples_data/matcap_00002.png --embed-file examples_data/matcap_00003.png --embed-file examples_data/matcap_00004.png -s USE_SDL=2 -o docs/examples/07_matcap.html

emcc -Iinclude -Isubmodules/imgui -Isubmodules/glm -Isubmodules/picojson -Isubmodules/ImGuiColorTextEdit \
               submodules/imgui/imgui.cpp \
               submodules/imgui/imgui_draw.cpp \
               submodules/ImGuiColorTextEdit/TextEditor.cpp \
               src/sre/Camera.cpp \
               src/sre/Color.cpp \
               src/sre/Framebuffer.cpp \
               src/sre/imgui_sre.cpp \
               src/sre/Inspector.cpp \
               src/sre/Light.cpp \
               src/sre/Log.cpp \
               src/sre/Material.cpp \
               src/sre/Mesh.cpp \
               src/sre/ModelImporter.cpp \
               src/sre/Renderer.cpp \
               src/sre/RenderPass.cpp \
               src/sre/Resource.cpp \
               src/sre/SDLRenderer.cpp \
               src/sre/Shader.cpp \
               src/sre/Skybox.cpp \
               src/sre/Sprite.cpp \
               src/sre/SpriteAtlas.cpp \
               src/sre/SpriteBatch.cpp \
               src/sre/Texture.cpp \
               src/sre/VR.cpp \
               src/sre/WorldLights.cpp \
               src/sre/impl/GL.cpp \
               src/sre/impl/UniformSet.cpp \
               examples/09_picking.cpp \
               -O2 -std=c++14 -s USE_WEBGL2=1 -s FORCE_FILESYSTEM=1 -s TOTAL_MEMORY=33554432 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='[]' -s USE_SDL=2 -o docs/examples/09_picking.html

emcc -Iinclude -Isubmodules/imgui -Isubmodules/glm -Isubmodules/picojson -Isubmodules/ImGuiColorTextEdit \
               submodules/imgui/imgui.cpp \
               submodules/imgui/imgui_draw.cpp \
               submodules/ImGuiColorTextEdit/TextEditor.cpp \
               src/sre/Camera.cpp \
               src/sre/Color.cpp \
               src/sre/Framebuffer.cpp \
               src/sre/imgui_sre.cpp \
               src/sre/Inspector.cpp \
               src/sre/Light.cpp \
               src/sre/Log.cpp \
               src/sre/Material.cpp \
               src/sre/Mesh.cpp \
               src/sre/ModelImporter.cpp \
               src/sre/Renderer.cpp \
               src/sre/RenderPass.cpp \
               src/sre/Resource.cpp \
               src/sre/SDLRenderer.cpp \
               src/sre/Shader.cpp \
               src/sre/Skybox.cpp \
               src/sre/Sprite.cpp \
               src/sre/SpriteAtlas.cpp \
               src/sre/SpriteBatch.cpp \
               src/sre/Texture.cpp \
               src/sre/VR.cpp \
               src/sre/WorldLights.cpp \
               src/sre/impl/GL.cpp \
               src/sre/impl/UniformSet.cpp \
               examples/15_cloth_simulation.cpp \
               -O2 -std=c++14 -s USE_WEBGL2=1 -s FORCE_FILESYSTEM=1 -s TOTAL_MEMORY=33554432 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='[]' -s USE_SDL=2 -o docs/examples/15_cloth_simulation.html

emcc -Iinclude -Isubmodules/imgui -Isubmodules/glm -Isubmodules/picojson -Isubmodules/ImGuiColorTextEdit \
               submodules/imgui/imgui.cpp \
               submodules/imgui/imgui_draw.cpp \
               submodules/ImGuiColorTextEdit/TextEditor.cpp \
               src/sre/Camera.cpp \
               src/sre/Color.cpp \
               src/sre/Framebuffer.cpp \
               src/sre/imgui_sre.cpp \
               src/sre/Inspector.cpp \
               src/sre/Light.cpp \
               src/sre/Log.cpp \
               src/sre/Material.cpp \
               src/sre/Mesh.cpp \
               src/sre/ModelImporter.cpp \
               src/sre/Renderer.cpp \
               src/sre/RenderPass.cpp \
               src/sre/Resource.cpp \
               src/sre/SDLRenderer.cpp \
               src/sre/Shader.cpp \
               src/sre/Skybox.cpp \
               src/sre/Sprite.cpp \
               src/sre/SpriteAtlas.cpp \
               src/sre/SpriteBatch.cpp \
               src/sre/Texture.cpp \
               src/sre/VR.cpp \
               src/sre/WorldLights.cpp \
               src/sre/impl/GL.cpp \
               src/sre/impl/UniformSet.cpp \
               examples/16_shadows.cpp \
               -O2 -std=c++14 -s USE_WEBGL2=1 -s FORCE_FILESYSTEM=1 -s TOTAL_MEMORY=33554432 --embed-file examples_data/suzanne.obj -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='[]' -s USE_SDL=2 -o docs/examples/16_shadows.html
