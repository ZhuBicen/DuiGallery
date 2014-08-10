{  
  'target_defaults': {
    'default_configuration': 'Debug',
    'configurations': {
      'Common_Base': {
        'abstract': 1,
        'msvs_configuration_attributes': {
          'CharacterSet': '1',
        },
        # Add the default import libs.
        'msvs_settings':{
          'VCLinkerTool': {
            'AdditionalDependencies': [
              'gdi32.lib',
              'Comctl32.lib',
			  'Advapi32.lib',
			  'User32.lib',
			  'DbgHelp.lib',
			  'Shell32.lib',
			  'Kernel32.lib',
			  'Ole32.lib',
			  'Psapi.lib',
			  'Comdlg32.lib',
            ],
          },
          'VCCLCompilerTool': {
            'RuntimeLibrary': '2', # nondebug dll
          },
        },
		'defines':[
			'WIN32',
		],
      },
      'Debug_Base': {
        'abstract': 1,
        'msvs_settings':{
          'VCLinkerTool': {
            'GenerateDebugInformation': 'true',
          },
          'VCCLCompilerTool': {
            'RuntimeLibrary': '3', # debug dll
          },
        },
      },
      'Debug': {
        'inherit_from': ['Common_Base', 'Debug_Base'],
        'defines': [
          '_DEBUG',
          'DEBUG',
        ],
      },
      'Release': {
        'inherit_from': ['Common_Base'],
        'defines': [
          'NDEBUG',
		  
        ],
      },
    }
  },
}
