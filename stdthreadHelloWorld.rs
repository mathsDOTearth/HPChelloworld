// use Rust std::thread to say helloworld from each thread

use std::thread;
use std::sync::Arc;

fn main() {
// hellothread program creates a string in shared memory and then
// each thread prints the string together with its thread number.

// find the number of threads the cpu can use
    let num_threads = match thread::available_parallelism() {
        Ok(count) => count.get(),
        Err(e) => {
            eprintln!("Failed to get available parallelism: {}. Defaulting to 4 threads.", e);
            4
        }
    };
    	
// create our message in shared memory
	let shared_message = Arc::new("Hello World!".to_string());
	
// Create and join threads
	let handles: Vec<_> = (0..num_threads).map(|i| {

// Create atomic reference to our shared message
		let thread_message = Arc::clone(&shared_message);
		
// Spawn the threads and print the message
		thread::spawn(move || {
            println!("{} from thread {}", thread_message, i);
        })
    }).collect();
    
// Wait for all threads to complete before end of main
    for handle in handles {
        handle.join().unwrap();
    }

// end of fn main()
}	
