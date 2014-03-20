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
      },
      'Debug': {
        'inherit_from': ['Common_Base'],
      },
      'Release': {
        'inherit_from': ['Common_Base'],
      },
    }
  },
}