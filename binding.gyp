{
  "targets": [
    {
      "target_name": "binding",
      "sources": [
        "src/binding.cc",
        "src/status.cc",
        "src/graph.cc",
        "src/session.cc"
      ],
      "include_dirs" : [
        #"/usr/local/include"
      ],
      'libraries': [
        '-ltensorflow'
      ]
    }
  ]
}
