# The imageRGB ADT
**Date:** 2025-11-26  
**Course:** Algorithms and Data Structures

This project implements and analyzes an **Abstract Data Type (ADT)** for RGB image processing, featuring advanced algorithms for image comparison, geometric transformations, and region-based segmentation.
The complete project report with detailed analysis, experimental results, and implementation details is available here: [**report**](./report.pdf)

## Authors
- Inês Batista (124877)
- Maria Quinteiro (124996)

## Project Goals

### Implementation
- Complete the imageRGB ADT supporting image creation, copying, and destruction
- Implement pixel manipulation using 2D array with LUT architecture
- Support PBM (P4) and PPM (P3) file formats

### Algorithm Development
- Image comparison with early termination optimization
- Geometric transformations (90° and 180° rotations)
- Three Region Growing strategies using Flood Fill algorithm

### Performance Analysis
- Instrumentation via PIXMEM counter for memory access measurement
- Empirical validation of computational complexity models
- Comparative analysis of different algorithm strategies


## Key Algorithms

### Image Comparison (`ImageIsEqual`)
- **Strategy:** Early termination on first difference detection
- **Complexity:** Best case Ω(1), Worst case O(w×h)
- **Instrumentation:** PIXMEM counts pixel memory accesses

### Geometric Transformations
- `ImageRotate90CW` - 90° clockwise rotation
- `ImageRotate180CW` - 180° rotation
- **Complexity:** O(w×h) for all transformations

### Region Growing (Flood Fill)
Three implemented strategies:

1. **Recursive Approach**
   - Simple implementation with depth-first search
   - Risk of stack overflow for large regions
   - Best for small images and prototyping

2. **Queue-based (BFS)**
   - Uses PixelCoordsQueue for breadth-first search
   - Uniform, isotropic region growth
   - Most robust for large regions (>1M pixels)

3. **Stack-based (DFS)** 
   - Uses PixelCoordsStack for depth-first search
   - Memory-efficient for thin structures
   - Preferred for memory-constrained systems
