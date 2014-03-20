{  
  'target_defaults': {
    'default_configuration': 'Debug',
    'configurations': {
      'Common_Base': {
        'abstract': 1,
        'msvs_configuration_attributes': {
          'OutputDirectory': '<(DEPTH)\\build\\$(ConfigurationName)',
          'IntermediateDirectory': '$(OutDir)\\obj\\$(ProjectName)',
          'CharacterSet': '1',
        },
        # Add the default import libs.
        'msvs_settings':{
          'VCLinkerTool': {
            'AdditionalDependencies': [
              'gdi32.lib',
              'Comctl32.lib',
            ],
          },
          'VCCLCompilerTool': {
            'RuntimeLibrary': '2', # /MD(nondebug dll)
          },
        },
      },
      'Debug_Base': {
        'abstract': 1,
        'msvs_settings':{
          'VCLinkerTool': {
            'GenerateDebugInformation': 'true',
          },
          'VCCLCompilerTool': {
            'RuntimeLibrary': '3', # /MDd(debug dll)
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
