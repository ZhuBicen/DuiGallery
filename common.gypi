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
              'kernel32.lib',
              'gdi32.lib',
              'winspool.lib',
              'comdlg32.lib',
              'advapi32.lib',
              'shell32.lib',
              'ole32.lib',
              'oleaut32.lib',
              'user32.lib',
              'uuid.lib',
              'odbc32.lib',
              'odbccp32.lib',
              'delayimp.lib',
              'credui.lib',
              'netapi32.lib',
              'Comctl32.lib',
            ],
            'GenerateDebugInformation': 'true',
          },
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
