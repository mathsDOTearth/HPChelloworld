// a Rust MPI helloworld program that will say helloworld 
// from each mpi process.
// dont forget to add mpi = "0.6" to dependencies in your cargo.toml

extern crate mpi;

use mpi::request::WaitGuard;
use mpi::traits::*;

fn main() {
    let universe = mpi::initialize().unwrap();
    let world = universe.world();
    let size = world.size();
    let rank = world.rank();

    println!("Hello, world from rank {} of {}", rank, size);
}
