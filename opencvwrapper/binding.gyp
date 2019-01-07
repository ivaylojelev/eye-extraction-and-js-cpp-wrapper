{
  "variables" : {
  },
  "targets": [
    {
      "target_name": "opencvwrapper",
      "include_dirs": [
          "<!(node -e \"require('nan')\")",
          "./common",
      ],
      'cflags': [
            '-Wall',
            '-Wparentheses',
            '-Winline',
            '-Wbad-function-cast',
            '-Wdisabled-optimization',
            '-g',
            '-O3',
            "-Wno-deprecated-declarations",
            "-Wsign-compare"
      ],
      'link_settings': {
                      'library_dirs' : [
                          '/opt/vc/lib',
                          './common'
                      ],
                      'libraries': [
                        '-lz',
                        './libopencvjs.so'
                      ],
                      "ldflags": [
                      ]
      },
      "sources": [
          "src/main.cc"
      ],

    }
  ]
}
