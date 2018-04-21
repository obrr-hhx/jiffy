namespace cpp elasticmem.directory

exception block_allocation_service_exception {
  1: string msg,
}

service block_allocation_service {
  void add_replica_to_chain(1: list<string> block_names)
    throws (1: block_allocation_service_exception ex),

  void remove_blocks(1: list<string> block_names)
    throws (1: block_allocation_service_exception ex),
}
