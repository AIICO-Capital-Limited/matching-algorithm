cmd_Release/obj.target/addon/addon.o := c++ -o Release/obj.target/addon/addon.o ../addon.cpp '-DNODE_GYP_MODULE_NAME=addon' '-DUSING_UV_SHARED=1' '-DUSING_V8_SHARED=1' '-DV8_DEPRECATION_WARNINGS=1' '-D_GLIBCXX_USE_CXX11_ABI=1' '-D_DARWIN_USE_64_BIT_INODE=1' '-D_LARGEFILE_SOURCE' '-D_FILE_OFFSET_BITS=64' '-DBUILDING_NODE_EXTENSION' -I/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node -I/Users/folaosibo/Library/Caches/node-gyp/22.7.0/src -I/Users/folaosibo/Library/Caches/node-gyp/22.7.0/deps/openssl/config -I/Users/folaosibo/Library/Caches/node-gyp/22.7.0/deps/openssl/openssl/include -I/Users/folaosibo/Library/Caches/node-gyp/22.7.0/deps/uv/include -I/Users/folaosibo/Library/Caches/node-gyp/22.7.0/deps/zlib -I/Users/folaosibo/Library/Caches/node-gyp/22.7.0/deps/v8/include "-I../\"/Users/folaosibo/Documents/AIICOInternshipProjects/MatchingAlgorithmCondensed/matchingAlgorithmPackage/node_modules/node-addon-api\""  -O3 -gdwarf-2 -fno-strict-aliasing -flto -mmacosx-version-min=11.0 -arch arm64 -Wall -Wendif-labels -W -Wno-unused-parameter -std=gnu++17 -stdlib=libc++ -fno-rtti -fno-exceptions -MMD -MF ./Release/.deps/Release/obj.target/addon/addon.o.d.raw   -c
Release/obj.target/addon/addon.o: ../addon.cpp ../Functions.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/node.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/cppgc/common.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8config.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-array-buffer.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-local-handle.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-handle-base.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-internal.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-object.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-maybe.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-persistent-handle.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-weak-callback-info.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-primitive.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-data.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-value.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-traced-handle.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-container.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-context.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-snapshot.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-isolate.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-callbacks.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-promise.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-debug.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-script.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-memory-span.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-message.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-embedder-heap.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-function-callback.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-microtask.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-statistics.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-unwinder.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-embedder-state-scope.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-date.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-exception.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-extension.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-external.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-function.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-template.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-initialization.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-platform.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-source-location.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-json.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-locker.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-microtask-queue.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-primitive-object.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-proxy.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-regexp.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-typed-array.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-value-serializer.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-version.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-wasm.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/node_version.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/node_api.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/js_native_api.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/js_native_api_types.h \
  /Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/node_api_types.h
../addon.cpp:
../Functions.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/node.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/cppgc/common.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8config.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-array-buffer.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-local-handle.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-handle-base.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-internal.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-object.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-maybe.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-persistent-handle.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-weak-callback-info.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-primitive.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-data.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-value.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-traced-handle.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-container.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-context.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-snapshot.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-isolate.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-callbacks.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-promise.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-debug.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-script.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-memory-span.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-message.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-embedder-heap.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-function-callback.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-microtask.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-statistics.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-unwinder.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-embedder-state-scope.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-date.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-exception.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-extension.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-external.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-function.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-template.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-initialization.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-platform.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-source-location.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-json.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-locker.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-microtask-queue.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-primitive-object.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-proxy.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-regexp.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-typed-array.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-value-serializer.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-version.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/v8-wasm.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/node_version.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/node_api.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/js_native_api.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/js_native_api_types.h:
/Users/folaosibo/Library/Caches/node-gyp/22.7.0/include/node/node_api_types.h:
