{
  'includes': [
    '../../common.gypi',
  ],
  'targets': [
    {
      'target_name': 'NativeButton',
      'type': 'executable',
      'include_dirs':[
        '<(DEPTH)/DuiLib'
      ],
      'dependencies': [
        '<(DEPTH)/DuiLib/DuiLib.gyp:DuiLib',
      ],
      'defines':[ 
        'UNICODE',
        '_UNICODE',	
      ],
      'sources': [
        'NativeButton.cpp',
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

