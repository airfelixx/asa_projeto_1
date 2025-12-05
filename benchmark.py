#!/usr/bin/env python3
"""
Benchmark script for projeto.cpp
Generates 15 test instances using gerador_p1.cpp and times the execution
"""
import subprocess
import time
import os

# Configuration
NUM_INSTANCES = 20
# Moderate sizes: N from 100 to 1500
INSTANCE_SIZES = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000]
MAX_POTENTIAL = 1000  # Pmax value for generator

def compile_programs():
    """Compile both C++ programs"""
    print("Compiling programs...")
    
    # Compile generator
    result = subprocess.run(
        ["g++", "-O2", "-o", "gerador_p1", "gerador_p1.cpp"],
        capture_output=True,
        text=True
    )
    if result.returncode != 0:
        print(f"Error compiling gerador_p1.cpp:\n{result.stderr}")
        return False
    
    # Compile project
    result = subprocess.run(
        ["g++", "-O2", "-o", "projeto", "projeto.cpp"],
        capture_output=True,
        text=True
    )
    if result.returncode != 0:
        print(f"Error compiling projeto.cpp:\n{result.stderr}")
        return False
    
    print("Compilation successful!")
    return True

def generate_instance(n, pmax, output_file):
    """Generate a test instance using gerador_p1"""
    result = subprocess.run(
        ["./gerador_p1", str(n), str(pmax)],
        capture_output=True,
        text=True
    )
    
    if result.returncode != 0:
        print(f"Error generating instance: {result.stderr}")
        return False
    
    with open(output_file, 'w') as f:
        f.write(result.stdout)
    
    return True

def time_execution(input_file, output_file):
    """Time the execution of projeto on a given input"""
    with open(input_file, 'r') as f:
        input_data = f.read()
    
    start_time = time.time()
    result = subprocess.run(
        ["./projeto"],
        input=input_data,
        capture_output=True,
        text=True
    )
    end_time = time.time()
    
    if result.returncode != 0:
        print(f"Error running projeto on {input_file}:\n{result.stderr}")
        return None
    
    execution_time = end_time - start_time
    
    with open(output_file, 'w') as f:
        f.write(result.stdout)
    
    return execution_time

def main():
    # Create directories for instances and outputs
    os.makedirs("instances", exist_ok=True)
    os.makedirs("outputs", exist_ok=True)
    os.makedirs("results", exist_ok=True)
    
    # Compile programs
    if not compile_programs():
        print("Compilation failed. Exiting.")
        return
    
    print(f"\nGenerating {NUM_INSTANCES} test instances...")
    
    # Results storage
    results = []
    
    for i in range(NUM_INSTANCES):
        n = INSTANCE_SIZES[i]
        
        instance_file = f"instances/instance_{i+1:02d}_n{n}.txt"
        output_file = f"outputs/output_{i+1:02d}_n{n}.txt"
        
        print(f"\nInstance {i+1}/{NUM_INSTANCES}: N={n}")
        
        # Generate instance
        print(f"  Generating {instance_file}...")
        if not generate_instance(n, MAX_POTENTIAL, instance_file):
            print(f"  Failed to generate instance {i+1}")
            continue
        
        # Time execution
        print(f"  Running projeto.cpp...")
        exec_time = time_execution(instance_file, output_file)
        
        if exec_time is not None:
            print(f"  Execution time: {exec_time:.6f} seconds")
            results.append((n, exec_time))
        else:
            print(f"  Failed to run instance {i+1}")
    
    # Save timing results
    results_file = "results/timing_results.txt"
    print(f"\nSaving results to {results_file}...")
    
    with open(results_file, 'w') as f:
        f.write("Instance_Size\tExecution_Time(s)\n")
        for n, exec_time in results:
            f.write(f"{n}\t{exec_time:.6f}\n")
    
    # Also save detailed results
    detailed_results_file = "results/detailed_results.txt"
    with open(detailed_results_file, 'w') as f:
        f.write("=" * 60 + "\n")
        f.write("Benchmark Results for projeto.cpp\n")
        f.write("=" * 60 + "\n\n")
        f.write(f"Number of instances: {len(results)}\n")
        f.write(f"Maximum potential value: {MAX_POTENTIAL}\n\n")
        f.write("-" * 60 + "\n")
        f.write(f"{'Instance':<10} {'Size (N)':<20} {'Time (seconds)':<20}\n")
        f.write("-" * 60 + "\n")
        
        for idx, (n, exec_time) in enumerate(results, 1):
            f.write(f"{idx:<10} {n:<20} {exec_time:<20.6f}\n")
        
        f.write("-" * 60 + "\n")
        
        if results:
            avg_time = sum(t for _, t in results) / len(results)
            min_time = min(t for _, t in results)
            max_time = max(t for _, t in results)
            
            f.write(f"\nAverage execution time: {avg_time:.6f} seconds\n")
            f.write(f"Minimum execution time: {min_time:.6f} seconds\n")
            f.write(f"Maximum execution time: {max_time:.6f} seconds\n")
    
    print("\n" + "=" * 60)
    print("Benchmark completed!")
    print("=" * 60)
    print(f"Instances saved in: instances/")
    print(f"Outputs saved in: outputs/")
    print(f"Results saved in: {results_file}")
    print(f"Detailed results saved in: {detailed_results_file}")
    
    if results:
        print(f"\nSummary:")
        print(f"  Successfully ran {len(results)} instances")
        avg_time = sum(t for _, t in results) / len(results)
        print(f"  Average execution time: {avg_time:.6f} seconds")

if __name__ == "__main__":
    main()
