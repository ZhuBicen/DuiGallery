{
  'includes': [
    '../../common.gypi',
  ],
  'targets': [
    {
      'target_name': '02_TitleBar',
      'type': 'executable',
      'include_dirs':[
        '<(DEPTH)/DuiLib/'
      ],
      'dependencies': [
        '<(DEPTH)/DuiLib/DuiLib.gyp:DuiLib',
      ],
      'defines':[ 
        'UNICODE',
        '_UNICODE',	
      ],
      'sources': [
        '02_TitleBar.cpp',
		'02_TitleBar.xml',
      ],
	  'configurations': {
		'Common_Base': {
		  'msvs_configuration_attributes': {
          'OutputDirectory': '$(ProjectDir)',
		  },
		},
	  }
    },
  ],
}

