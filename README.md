# The imageRGB ADT
**Date:** 2025-11-15

This project was developed for the course Algorithms and Data Structures.  
Its main goal is to implement and analyze an **Abstract Data Type (ADT)** for representing and manipulating RGB images, along with functions for comparison, geometric transformations, and region-based segmentation.

The full project report is available here: [Project Report](./report.pdf)

## Authors
Inês Batista, 124877<br>
Maria Quinteiro, 124996

## Project Goals

- Implement the **imageRGB ADT**, supporting:
  - Creation, copying, and destruction of images
  - Pixel manipulation using a 2D array of color indices
  - Mapping of indices to actual RGB values via a Look-Up Table (LUT)
  - Loading and saving images in **PBM (P4)** and **PPM (P3)** formats

- Develop and analyze algorithms for:
  - Image comparison
  - Geometric transformations (90° and 180° rotations)
  - Region Growing (Flood Fill) using three different strategies

- Use an instrumentation module to measure:
  - Number of pixel memory accesses (PIXMEM counter)
  - Time and resource consumption of different approaches

## Internal Structure of the imageRGB ADT

Each image is represented by:
- `width`, `height` — image dimensions  
- `image` — a 2D array storing indices into the LUT  
- `LUT` — a Look-Up Table storing actual RGB triplets  
- `num_colors` — number of active colors

This architecture separates **geometry** from **color information**, which:
- saves memory (especially for repeated colors),
- improves data locality,
- allows efficient comparisons and transformations.
