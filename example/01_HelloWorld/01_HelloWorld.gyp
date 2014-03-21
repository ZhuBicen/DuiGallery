{
  'includes': [
    '../../common.gypi',
  ],
  'targets': [
    {
      'target_name': '01_HelloWorld',
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
        '01_HelloWorld.cpp',
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

