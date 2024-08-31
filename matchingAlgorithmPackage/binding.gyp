{
    "targets" : [
        {
            "target_name": "addon",
            "sources": ["addon.cpp"],
            # "dependencies": ["<!(node -p \"require('node-addon-api').include\")"],
            "include_dirs": ["<!(node -p \"require('node-addon-api').include\")"],
            "cflags_cc": ["-fexceptions"],
            "cflags": ["-std=c++20"]
        }
    ]
}