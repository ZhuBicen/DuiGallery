{
  'includes': [
    '../../common.gypi',
  ],
  'targets': [
    {
      'target_name': '03_ListDemo',
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
        'Main.cpp',
		'MenuWnd.h',
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

