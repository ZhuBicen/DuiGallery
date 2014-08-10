{
  'includes': [
    '../../common.gypi',
    '../../CEF/cef_paths2.gypi',
  ],
  'targets': [
    {
      'target_name': 'SimpleCEF',
      'type': 'executable',
      'include_dirs':[
        '<(DEPTH)/DuiLib',
        '<(DEPTH)/CEF/include',
      ],
      'dependencies': [
        '<(DEPTH)/DuiLib/DuiLib.gyp:DuiLib',
        '<(DEPTH)/CEF/cefclient.gyp:libcef_dll_wrapper',
      ],
      'defines':[ 
        'UNICODE',
        '_UNICODE',	
        'USING_CEF_SHARED',
      ],
      'sources': [
        'NativeWindow.hpp',
        'MainWindow.hpp',
        'SimpleCEF.cpp',
      ],
      'link_settings': {
        'libraries':[
          '-lcomctl32.lib',
          '-lshlwapi.lib',
          '-lrpcrt4.lib',
          '-l<(DEPTH)/$(ConfigurationName)/libcef.lib',
        ],
      },
      'library_dirs': [
        # Needed to find cef_sandbox.lib using #pragma comment(lib, ...).
        '<(DEPTH)/$(ConfigurationName)',
      ],
      'configurations': {
        'Common_Base': {
          'msvs_configuration_attributes': {
            'OutputDirectory': '$(ProjectDir)',
          },
        },
      },
    },
  ],
}

