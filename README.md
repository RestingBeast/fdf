*This project has been created as part of the 42 curriculum by kkhant-z.*

# Description

**FdF** (Fil de Fer) is a 3D wireframe graphics software project developed in C. The goal of this project is to create a simple graphical interface that reads a file containing coordinates and terrain altitude markers (`.fdf` format) and renders a dynamic, stylized 3D perspective landscape using isometric projection.

The program parses raw matrix arrays representing geometric heightmaps, calculates the trigonometric matrix transformations required to map those points into a 3D isometric plane, and draws custom-colored vectors connecting adjacent coordinates to reconstruct solid landscapes, mountains, and grids.

---

# Instructions

### Compilation

The project includes a standard automated `Makefile` compilation workflow. To build the executable, open your terminal at the root directory of the repository and execute:

```bash
make
```

To clear temporary object files created during processing, use:

```bash
make clean
```

To purge all built assets, object binaries, and the final executable, execute:

```bash
make fclean
```

To force a clean, complete rebuild from scratch:

```bash
make re
```

ExecutionRun the compiled fdf binary by passing a target map file as its single configuration parameter:

```bash
./fdf maps.fdf
```

# Resources

- man
- [MiniLibX Doc](https://harm-smits.github.io/42docs/libs/minilibx/colors.html)
- [Walkthrough](https://medium.com/@amehri_tarik/fdf-42-a-detailed-walkthrough-7184cca317fc)

# AI Usage

AI used in

- calculating scale
- finding camera position
- decoding color
- implementing Bresenham's line drawing algorithm
- Debugging
*This project has been created as part of the 42 curriculum by kkhant-z.*

# Description

**FdF** (Fil de Fer) is a 3D wireframe graphics software project developed in C. The goal of this project is to create a simple graphical interface that reads a file containing coordinates and terrain altitude markers (`.fdf` format) and renders a dynamic, stylized 3D perspective landscape using isometric projection.

The program parses raw matrix arrays representing geometric heightmaps, calculates the trigonometric matrix transformations required to map those points into a 3D isometric plane, and draws custom-colored vectors connecting adjacent coordinates to reconstruct solid landscapes, mountains, and grids.

---

# Instructions

### Compilation

The project includes a standard automated `Makefile` compilation workflow. To build the executable, open your terminal at the root directory of the repository and execute:

```bash
make
```

To clear temporary object files created during processing, use:

```bash
make clean
```

To purge all built assets, object binaries, and the final executable, execute:

```bash
make fclean
```

To force a clean, complete rebuild from scratch:

```bash
make re
```

ExecutionRun the compiled fdf binary by passing a target map file as its single configuration parameter:

```bash
./fdf maps.fdf
```

# Resources

- man
- [MiniLibX Doc](https://harm-smits.github.io/42docs/libs/minilibx/colors.html)
- [Walkthrough](https://medium.com/@amehri_tarik/fdf-42-a-detailed-walkthrough-7184cca317fc)

# AI Usage

AI used in

- calculating scale
- finding camera position
- decoding color
- implementing Bresenham's line drawing algorithm
- Debugging

