{
  'includes': [
    '../../common.gypi',
  ],
  'targets': [
    {
      'target_name': 'maxinfo',
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
        'maxinfo.cpp',
		'maxinfo.xml',
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

