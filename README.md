*This project has been created as part of the 42 curriculum by <rcompain>, <pchazalm>.*

---

![MiniRT render](screenshots/your_screenshot_here.png)

---

# MiniRT — A Ray Tracer from Scratch

A physically-inspired ray tracer written in C, capable of rendering 3D scenes described in plain-text files — including a real-time gravitational simulation of a solar system.

---

## Table of Contents

- [Description](#description)
- [Features](#features)
- [How Ray Tracing Works](#how-ray-tracing-works)
  - [The Scene Does Not Exist](#the-scene-does-not-exist)
  - [The Camera and the Viewport](#the-camera-and-the-viewport)
  - [Casting Rays](#casting-rays)
  - [Intersections](#intersections)
    - [Sphere](#sphere)
    - [Plane](#plane)
    - [Cylinder](#cylinder)
  - [Lighting](#lighting)
    - [Ambient Light](#ambient-light)
    - [Diffuse Light](#diffuse-light)
    - [Specular Light](#specular-light)
    - [Putting It All Together](#putting-it-all-together)
  - [Shadows](#shadows)
  - [Textures and UV Mapping](#textures-and-uv-mapping)
  - [Bump Mapping](#bump-mapping)
  - [Gamma Correction](#gamma-correction)
- [Physics Simulation](#physics-simulation)
  - [The N-Body Problem](#the-n-body-problem)
  - [Why Not Euler Integration](#why-not-euler-integration)
  - [Why Not Barnes-Hut](#why-not-barnes-hut)
  - [Verlet Integration](#verlet-integration)
  - [Units](#units)
- [Instructions](#instructions)
  - [Dependencies](#dependencies)
  - [Compilation](#compilation)
  - [Execution](#execution)
  - [Controls](#controls)
- [Scene File Formats](#scene-file-formats)
  - [Mandatory — .rt Format](#mandatory----rt-format)
  - [Bonus — .rt Format](#bonus----rt-format)
  - [Solar — .solar Format](#solar----solar-format)
- [Resources](#resources)

---

## Description

MiniRT renders 3D scenes from a text file. The file describes where the camera is, what objects are in the scene, and how they are lit. The program reads this file, computes the color of every pixel on screen, and displays the result in a window.

There are three build modes:

| Mode | File type | What it does |
|---|---|---|
| `make` | `.rt` | Renders spheres, planes, cylinders with basic lighting |
| `make bonus` | `.rt` | Adds specular highlights, shadows, image textures, bump maps, chessboard patterns |
| `make bonus` | `.solar` | Everything above, plus a real-time gravitational N-body simulation |

The graphics window is provided by **MacroLibX**, a lightweight C++ graphics library using Vulkan, developed for 42 school projects on Linux.

---

## Features

**Mandatory**
- Three geometric primitives: sphere, plane, cylinder (with closed caps)
- Configurable camera with position, orientation and field of view
- Ambient and diffuse lighting
- Scene described in a `.rt` text file with strict validation and error messages
- Real-time camera navigation

**Bonus**
- Specular highlights (Phong model)
- Hard shadows
- Image texture mapping (PNG) on all primitives
- Bump mapping (normal perturbation from a grayscale height map)
- Procedural chessboard texture
- Gamma correction

**Solar**
- Each sphere can be given a mass and an initial velocity
- N-body gravitational simulation running in real time using Verlet integration
- Physically accurate orbits (AU / solar mass / day unit system)
- Pre-built maps: full Solar System, binary star system, Solar System with major moons

---

## How Ray Tracing Works

### The Scene Does Not Exist

When you look at a photograph, you see light that bounced off real objects and hit a camera sensor. In a ray tracer, there are no real objects. There is no light, no camera, no table, no sphere. There is only mathematics.

A sphere, in MiniRT, is nothing more than this idea:

> *A sphere is the set of all points in space that are at exactly distance r from a center point C.*

That is the entire definition. There is no mesh, no triangles, no GPU buffer. Just a center position and a radius stored in memory. The renderer's job is to answer one question for every pixel on screen:

> **If a ray of light traveled from my eye through this pixel and into the scene, what would it hit, and what color would that be?**

Everything — shapes, light, shadows, textures — is the answer to that question, computed mathematically for millions of pixels.

---

### The Camera and the Viewport

The camera is defined by a position in 3D space, a direction it looks toward, and a field of view (FOV) angle.

To render an image, we build an invisible rectangle in front of the camera called the **viewport**. It represents the "window" through which we look at the scene. Every pixel on screen corresponds to one point on this viewport.

```
                      VIEWPORT
                   _______________
                  |       |       |
         FOV -->  |  pixel|       |
    [CAMERA] -----+-------+-------+-----> (into the scene)
                  |               |
                  |_______________|

           <------- focal length ------->
```

The size and shape of the viewport is computed from the FOV and the aspect ratio of the window:

- A wide FOV → large viewport → wide-angle lens effect
- A narrow FOV → small viewport → telephoto lens effect

The corner of the viewport, its horizontal extent and its vertical extent are pre-computed once per frame (or whenever the camera moves), then used to generate all rays.

---

### Casting Rays

For each pixel at position (x, y) on screen, we normalize those coordinates to the range [0, 1] and compute a **ray**:

```
ray.origin    = camera position
ray.direction = normalize( viewport_corner
                          + x * horizontal_vector
                          + y * vertical_vector
                          - camera position )
```

A ray is simply a point in space plus a direction. We can write any point along the ray as:

```
P(t) = origin + t * direction
```

where `t` is a scalar representing "how far along the ray". `t = 0` is the camera. `t = 1` is one unit forward. `t = 10` is ten units forward. Negative `t` is behind the camera.

```
      t=0        t=1        t=5
      [CAM] ------o----------o----------->
```

The goal is to find, for each ray, the smallest positive value of `t` at which the ray touches an object.

---

### Intersections

#### Sphere

We want to know: for what value of `t` does the ray `P(t) = O + t*D` touch the sphere of center `C` and radius `r`?

The mathematical definition of the sphere says that any point `P` on its surface satisfies:

```
||P - C||² = r²
```

(The distance from P to the center equals r.)

We substitute the ray equation for `P`:

```
||O + t*D - C||² = r²
```

Let `oc = O - C` (vector from sphere center to ray origin). Expanding:

```
(t*D + oc) · (t*D + oc) = r²
t²(D·D) + 2t(oc·D) + (oc·oc) - r² = 0
```

This is a standard quadratic equation `at² + 2bt + c = 0`, with:

```
a = D · D
b = oc · D
c = oc · oc - r²
```

The **discriminant** `Δ = b² - ac` tells us how many intersections exist:

```
        Δ < 0          Δ = 0           Δ > 0
    (no intersection) (tangent)    (two intersections)

         \   /           |              \ /
          \ /            |           ___X___
           X             |          /   |   \
          / \           _|_        /    |    \
         /   \         / | \      /     |     \
```

If `Δ ≥ 0`, the two solutions are:

```
t = (-b ± sqrt(Δ)) / a
```

We take the smallest positive `t` (nearest intersection in front of the camera). Values below `0.001` are discarded to avoid self-intersection artifacts.

---

#### Plane

Applying the same substitution approach to the plane equation `(P - P0) · N = 0` (a plane defined by a point `P0` and a normal `N`), we obtain directly:

```
t = ((P0 - O) · N) / (D · N)
```

If `D · N ≈ 0`, the ray is parallel to the plane and no intersection exists.

---

#### Cylinder

For a cylinder with axis direction `v`, center `C`, radius `r` and height `h`, we first decompose the ray into components **parallel** and **perpendicular** to the axis, then apply the same quadratic approach on the perpendicular component only. Once a `t` is found, we verify that the hit point lies within `[-h/2, h/2]` along the axis. The two flat **caps** are each tested as a disk (plane intersection + distance-from-center check).

---

### Lighting

Once we know which object a ray hits, and at what point, we compute the color of that pixel using the **Phong lighting model**. This model splits the contribution of light into three separate components that are summed together.

```
     Final Color = Ambient + Diffuse + Specular
```

---

#### Ambient Light

Ambient light represents indirect illumination — light that has bounced around the environment so many times that it comes equally from all directions. It is a flat, uniform addition to every surface regardless of its orientation.

```
         Scene without ambient          Scene with ambient
         ____________________           ____________________
        |                    |         |                    |
        |    ( sphere )      |         |    ( sphere )      |
        |   dark side = BLACK|         |   dark side = dim  |
        |____________________|         |____________________|
```

In our implementation, ambient light has a color and a ratio (intensity):

```
ambient_contribution = (ambient_color / 255) * ambient_ratio
```

---

#### Diffuse Light

Diffuse light represents direct illumination scattered equally in all directions from a surface. The key insight is: **a surface facing directly toward the light receives more light than one facing away**.

This is captured by the **dot product** between the surface normal `N` (the vector perpendicular to the surface at the hit point) and the direction toward the light `L`:

```
        Light source
             *
            /|
           / |
          /  |
         / θ |  <-- angle θ between L and N
        /    N (surface normal)
       /_____|
      [  surface  ]

    coef_diffuse = N · L = cos(θ)
```

- If `θ = 0°` (surface faces the light directly) → `cos(θ) = 1.0` → maximum brightness
- If `θ = 90°` (surface is perpendicular to the light) → `cos(θ) = 0.0` → no contribution
- If `θ > 90°` (surface faces away) → negative, clamped to 0

```
diffuse_contribution = (light_color / 255) * coef_diffuse * light_intensity
```

---

#### Specular Light

Specular light creates the shiny highlights you see on glossy surfaces. Unlike diffuse light (which scatters equally), specular light depends on **where the viewer is**. The highlight appears where the reflection of the light ray is aimed directly at the camera.

```
              Light
               *
                \
                 \  L          R (reflection of L around N)
                  \ |        /
                   \|      /
            --------N----/----------  surface
                      \  /
                       \/
                        V (direction to camera)
```

The reflection vector `R` is computed from the surface normal and the light direction:

```
R = 2 * (N · L) * N - L
```

The specular coefficient is:

```
coef_specular = max(0, R · V) ^ SHININESS
```

`SHININESS` (set to 32) controls how tight the highlight is. Higher value = smaller, sharper highlight.

```
specular_contribution = (light_color / 255) * coef_specular * KS * light_intensity
```

where `KS = 0.5` is the specular strength.

---

#### Putting It All Together

```
final_light = clamp(ambient + diffuse + specular, 0.0, 1.0)
pixel_color = object_color * final_light
```

Each channel (R, G, B) is computed independently using these same equations.

---

### Shadows

After computing the hit point, before applying diffuse and specular, we check whether anything blocks the path between the hit point and the light source. If so, the point is in shadow and only ambient light applies.

This is done by casting a **shadow ray** from the hit point toward the light:

```
shadow_ray.origin    = hit_point + 0.001 * N   (small offset to avoid self-shadowing)
shadow_ray.direction = normalize(light_pos - hit_point)
```

If this ray hits any object at a distance smaller than the distance to the light, the point is in shadow.

```
           *  Light
          /|
         / |
        /  |              [Shadow Ray] blocked → point is in shadow
  [OBJ A]  |               *light
            \             /|
             \      [B]--X |     (X = blocked by object A)
              \    /      \|
               \  /     [OBJ B] in shadow
                \/
```

The `0.001` epsilon offset on the origin is essential. Without it, the shadow ray would immediately re-intersect the surface it just hit (due to floating-point imprecision), causing every point to incorrectly shadow itself — a visual artifact known as **shadow acne**.

---

### Textures and UV Mapping

Instead of a flat color, an object can display an image (a PNG file) on its surface. To do this, for each hit point we compute **(u, v)** coordinates — two numbers between 0 and 1 that identify a position in the image, like coordinates inside a rectangle.

```
     Image (the texture)
     ___________________
    |(0,1)       (1,1)  |
    |                   |
    |      (u, v)       |
    |         *         |
    |                   |
    |(0,0)       (1,0)  |
    |___________________|
```

The challenge is mapping a 3D surface onto this 2D rectangle in a way that looks natural.

**For a sphere**, we use angles:

```
u = 0.5 + atan2(Pz, Px) / (2π)     (longitude, 0 to 1 around the equator)
v = 0.5 + asin(Py) / π              (latitude, 0 at south pole, 1 at north pole)
```

where `(Px, Py, Pz)` is the normalized hit point relative to the sphere center.

**For a plane**, two tangent vectors orthogonal to the surface normal are computed, and `u`, `v` are the projections of the hit point onto those vectors.

**For a cylinder**, the angle around the axis gives `u`, and the height along the axis gives `v`. The caps use the same tangent-based method as the plane.

#### Chessboard

As an alternative to an image, a procedural chessboard pattern can be generated. The UV coordinates are divided into tiles, and the parity of the tile index determines which of two colors to use:

```
tile_index = floor(u / scale) + floor(v / scale)
color = (tile_index is even) ? color1 : color2
```

---

### Bump Mapping

Bump mapping is a technique that makes a smooth surface *look* rough without adding any geometry. Instead of changing the shape of the object, it slightly tilts the surface normal at each point according to a **height map** image (a grayscale PNG where brightness encodes elevation).

```
    Smooth sphere          Bump-mapped sphere
         ___                    ___
        /   \                  / ~ \
       |     |                | ~   |
        \   /                  \ ~ /
         ---                    ---
    Normal always            Normal perturbed
    points outward           at each pixel
```

At a hit point with UV coordinates `(u, v)`, we sample three nearby points in the height map:

```
h        = brightness at (u,     v)
h_next_u = brightness at (u+du,  v)
h_next_v = brightness at (u,     v+dv)

gradient_u = h_next_u - h
gradient_v = h_next_v - h
```

These gradients represent how fast the elevation changes in each direction. The normal is then offset along the surface's tangent and bitangent vectors:

```
new_normal = normalize( normal + gradient_u * tangent + gradient_v * bitangent )
```

The result is a surface that appears to have ridges, craters or bumps under lighting, without any extra geometry cost.

---

### Gamma Correction

Computer screens do not display colors linearly. A pixel with value 128 (half of 255) does not appear half as bright as 255 to the human eye. To compensate, a **gamma correction** is applied to the final color before display:

```
final_channel = 255 * (lit_channel / 255) ^ GAMMA     (GAMMA = 0.8)
```

Without this, dark areas look too dark and the overall image appears flat and crushed. Gamma correction restores a natural-looking tonal range.

---

## Physics Simulation

The solar mode adds a real-time gravitational N-body simulation. Every physics-enabled sphere (planet, moon, star) attracts every other physics-enabled sphere according to Newton's law of gravitation, and their positions are updated at every frame.

### The N-Body Problem

The **N-body problem** is the challenge of simulating the motion of N objects that all exert gravitational force on each other simultaneously. For N = 2 (e.g. Earth + Sun), there is a perfect mathematical solution. For N ≥ 3, there is no closed-form solution — the system must be integrated numerically step by step.

At each step:
1. Compute the gravitational acceleration on each body from all other bodies
2. Update positions based on those accelerations

The gravitational force between two bodies `i` and `j` is:

```
F = G * m_i * m_j / d²

direction: from i toward j (attractive)
```

In terms of acceleration applied to body `i`:

```
acc_i += G * m_j / d²  *  normalize(pos_j - pos_i)
acc_j -= G * m_i / d²  *  normalize(pos_j - pos_i)   (Newton's third law)
```

We compute all pairs at once (O(N²) complexity) then apply all accelerations simultaneously — this prevents order-of-evaluation artifacts.

---

### Why Not Euler Integration

The simplest integration method is **Euler integration**:

```
velocity += acceleration * dt
position += velocity * dt
```

It is intuitive but has a fundamental flaw: it **adds energy to the system** over time. A planet in a circular orbit will gradually spiral outward, its orbit growing larger and larger until it flies off to infinity. For short simulations this is acceptable, but for a solar system running frame after frame, Euler integration destroys the simulation within minutes.

```
    EULER (orbit over time)        VERLET (orbit over time)

         __                              ____
       /    \                          /      \
      / t=0  \         vs.            |  t=0   |
     |    t=1 |                       |    t=1 |
      \   t=2/                         \      /
        \__/ <-- drifting outward        ----   <-- stable
```

---

### Why Not Barnes-Hut

**Barnes-Hut** is an optimization algorithm that reduces the N-body computation from O(N²) to O(N log N) by grouping distant bodies into clusters and approximating their combined gravitational effect. It is used in large-scale astrophysics simulations with millions of bodies.

In our case, the Solar System has at most a few dozen objects. The O(N²) brute-force approach is not only simpler to implement correctly, it is also perfectly fast for this scale. Barnes-Hut would add significant complexity (octree construction, center-of-mass approximation) with no measurable benefit.

---

### Verlet Integration

**Verlet integration** solves the energy-drift problem of Euler without storing velocity explicitly. It works by keeping track of the **previous** and **current** positions, and deriving the next position from them:

```
new_position = 2 * current_position - previous_position + acceleration * dt²
```

The velocity is implicitly encoded in the difference `current - previous`. This method conserves energy much better than Euler because the errors in position and velocity are correlated and cancel each other over time.

```
      prev_pos     cur_pos     new_pos
         o -------- o -------- o
              Δ1        Δ2

    Δ2 ≈ Δ1 + acc * dt²    (the step grows or shrinks based on acceleration)
```

After each step:
```
prev_pos  ←  cur_pos
cur_pos   ←  new_pos
sphere.center  ←  cur_pos   (so the renderer sees the updated position)
```

To achieve smooth and accurate orbits, **60 Verlet steps are executed per rendered frame**. Each step uses `dt = 0.01` simulated days, so each visual frame represents `60 × 0.01 = 0.6` simulated days.

---

### Units

Working in SI units (meters, kilograms, seconds) would require enormous numbers and floating-point precision problems. Instead, we use an astronomical unit system:

| Quantity | Unit | Value in SI |
|---|---|---|
| Distance | 1 AU (Astronomical Unit) | 1.496 × 10¹¹ m |
| Mass | 1 Solar mass | 1.989 × 10³⁰ kg |
| Time | 1 day | 86 400 s |

In these units, the gravitational constant becomes:

```
G = 2.959122 × 10⁻⁴   AU³ / (solar_mass · day²)
```

Initial velocities in the scene files are given in AU/day. Earth's orbital velocity, for example, is approximately `0.0172 AU/day`.

---

## Instructions

### Dependencies

MiniRT uses MacroLibX (included as a Git submodule) which requires Vulkan and X11:

```bash
# Ubuntu / Debian
sudo apt-get install build-essential cmake libvulkan-dev libx11-dev libxext-dev

# Arch Linux
sudo pacman -S base-devel cmake vulkan-headers libx11 libxext
```

A Vulkan-compatible GPU driver is required. On virtual machines, ensure Vulkan support is enabled.

### Compilation

```bash
# Clone the repository with submodules
git clone --recurse-submodules https://github.com/Remi-cpn/MiniRT.git
cd MiniRT

# Mandatory version
make

# Bonus version (textures, shadows, physics)
make bonus

# Clean object files
make clean

# Full clean (objects + binary)
make fclean

# Rebuild from scratch
make re
```

The Makefile automatically selects `Mandatory/` or `Bonus/` as the source directory based on the build target. MacroLibX is compiled automatically as part of the build.

### Execution

```bash
# Mandatory — basic ray tracer
./minirt path/to/scene.rt

# Bonus — with textures and shadows
./minirt path/to/scene.rt

# Bonus — solar simulation (detected via .solar extension)
./minirt path/to/scene.solar
```

Example scenes are available in `Mandatory/maps/` and `Bonus/maps/`:

```bash
./minirt Mandatory/maps/basic.rt
./minirt Bonus/maps/solar_system.solar
./minirt Bonus/maps/Double_sun.solar
./minirt Bonus/maps/with_mune.solar
```

Texture files for the solar maps must be placed in a `texture_map/` folder in the working directory (see [Solar System Scope textures](#resources)).

---

### Controls

Controls are identical across all three modes (mandatory, bonus `.rt`, and `.solar`). In solar mode, the camera moves while the simulation runs continuously in the background regardless of input.

| Key | Action |
|---|---|
| `W` | Move camera forward |
| `S` | Move camera backward |
| `A` | Strafe camera left |
| `D` | Strafe camera right |
| `SPACE` | Move camera up |
| `CTRL` | Move camera down |
| `↑` | Rotate camera upward (pitch) |
| `↓` | Rotate camera downward (pitch) |
| `←` | Rotate camera left (yaw) |
| `→` | Rotate camera right (yaw) |
| `I` | Increase field of view |
| `O` | Decrease field of view |
| `R` | Reload and reparse the scene file (resets camera and objects to file values) |
| `ESC` | Quit |
| Window close button | Quit |

> `R` is useful for live-editing your `.rt` file in a text editor and seeing the result instantly without restarting the program.

---

## Scene File Formats

All scene files use **space-separated fields**. Each line starts with an identifier that determines what the line describes. The order of lines in the file does not matter.

**General rules (all formats):**
- Fields are separated by **single spaces**
- Vectors and colors use **comma-separated values with no spaces**: `x,y,z` or `R,G,B`
- Lines starting with `#` are **comments** (bonus and solar only — not supported in mandatory)
- Empty lines are ignored
- Any formatting error causes the program to exit with an explicit error message

---

### Mandatory — .rt Format

**Required elements** (each must appear exactly once):

| Identifier | Fields | Rules |
|---|---|---|
| `A` | `ratio R,G,B` | `ratio` must be in [0.0, 1.0]. Colors in [0, 255] |
| `C` | `x,y,z dx,dy,dz fov` | Direction vector must be normalized (length = 1.0 ± 0.001). `fov` must be in ]0, 180[ |
| `L` | `x,y,z intensity R,G,B` | `intensity` must be in [0.0, 1.0]. Colors in [0, 255] |

**Objects** (can appear any number of times, in any order):

| Identifier | Fields | Rules |
|---|---|---|
| `sp` | `x,y,z diameter R,G,B` | `diameter` > 0. The parser stores `radius = diameter / 2` |
| `pl` | `x,y,z nx,ny,nz R,G,B` | Normal vector must be normalized (length = 1.0 ± 0.001) |
| `cy` | `x,y,z ax,ay,az diameter height R,G,B` | Axis must be normalized. `diameter` > 0. `height` > 0 |

**Minimal example:**

```
A 0.2 255,255,255
C 0,0,-5 0,0,1 70
L 2,3,-2 0.8 255,255,255
sp 0,0,3 1.0 255,0,0
pl 0,-1,0 0,1,0 180,180,180
cy 2,0,3 0,1,0 0.5 2.0 0,100,255
```

**Rules summary:**
- Exactly 1 `A`, 1 `C`, 1 `L` — no more, no fewer
- At least 0 objects (a scene with only ambient + camera + light is valid)
- No extra fields on any line
- No comments (`#` lines will cause a parse error)
- Floating-point values accept both `1.0` and `1` notation
- Scientific notation is **not** supported in mandatory

---

### Bonus — .rt Format

All mandatory rules apply. Additionally:

**Comments** are supported:
```
# This is a comment
```

**Objects can have an optional texture or chessboard field** appended after the base color.

**Image texture** (path to a PNG file):
```
sp  x,y,z diameter R,G,B texture.png
sp  x,y,z diameter R,G,B texture.png bump.png
pl  x,y,z nx,ny,nz R,G,B texture.png
pl  x,y,z nx,ny,nz R,G,B texture.png bump.png
cy  x,y,z ax,ay,az diameter height R,G,B texture.png
cy  x,y,z ax,ay,az diameter height R,G,B texture.png bump.png
```

**Chessboard pattern** (scale + second color):
```
sp  x,y,z diameter R,G,B scale R2,G2,B2
pl  x,y,z nx,ny,nz R,G,B scale R2,G2,B2
cy  x,y,z ax,ay,az diameter height R,G,B scale R2,G2,B2
```

**How the parser distinguishes texture from chessboard:**
The optional 4th field (after base color) is tested as a valid floating-point number. If it parses as a number → chessboard. If not (it is a string) → texture path.

**Rules:**
- Texture path is relative to the working directory of the binary
- `bump.png` is optional — a texture can be specified without a bump map
- Chessboard `scale` must be > 0
- A chessboard requires **both** `scale` and the second color `R2,G2,B2`
- A bump map requires a base texture — you cannot specify a bump map without a texture

**Examples:**
```
# Sphere with image texture only
sp 0,0,3 2.0 255,255,255 texture_map/2k_earth.png

# Sphere with texture and bump map
sp 0,0,3 2.0 255,255,255 texture_map/moon.png texture_map/moon_bump.png

# Plane with chessboard (tile size 1.0, white and black)
pl 0,-1,0 0,1,0 255,255,255 1.0 0,0,0

# Cylinder with texture
cy 0,0,2 0,1,0 1.0 3.0 200,200,200 texture_map/metal.png
```

---

### Solar — .solar Format

Used with `make bonus`. The `.solar` extension is detected automatically at runtime — no special flag is needed. Activating solar mode enables the physics simulation.

`A`, `C`, and `L` lines are identical to the bonus `.rt` format.

**Only spheres are supported as objects.** They use an extended format:

```
sp  x,y,z diameter R,G,B texture.png [mass vx,vy,vz]
```

| Field | Type | Description |
|---|---|---|
| `x,y,z` | float | Initial position in AU |
| `diameter` | float > 0 | Visual diameter in AU |
| `R,G,B` | int [0,255] | Fallback color (used if texture fails to load) |
| `texture.png` | string | Path to PNG texture (required) |
| `mass` | float > 0 | Mass in solar masses. **Omit to make the body static (not simulated)** |
| `vx,vy,vz` | float | Initial velocity in AU/day. **Required if mass is provided** |

**Rules:**
- A body without `mass` is rendered but never moves, regardless of gravity from other bodies
- A body with `mass` but without `vx,vy,vz` will cause a parse error
- Scientific notation is supported for mass and velocity: `3.003e-6`, `0.0172`, `1.65e-7`
- Planes and cylinders are not supported in `.solar` files
- Comments (`#`) are supported
- The texture field is **not optional** in solar format (unlike bonus `.rt` where texture is optional)

**Minimal solar example:**
```
A 0.2 255,255,255
C 0,2,5 0,-0.3,-1 70
L 0,0,0 1.0 255,255,200

# Sun — static (no mass/velocity)
sp 0,0,0 0.5 255,220,0 texture_map/2k_sun.png 1.0 0,0,0

# Earth — physics enabled
sp 1,0,0 0.05 100,150,255 texture_map/2k_earth.png 3.003e-6 0,0.0172,0
```

**Reference orbital velocities (AU/day):**

| Body | Velocity |
|---|---|
| Mercury | 0.0274 |
| Venus | 0.0202 |
| Earth | 0.0172 |
| Mars | 0.0139 |
| Jupiter | 0.00754 |
| Saturn | 0.00558 |
| Uranus | 0.00392 |
| Neptune | 0.00313 |

---

## Resources

**Ray Tracing**

- [Ray Tracing in One Weekend — Peter Shirley](https://raytracing.github.io/books/RayTracingInOneWeekend.html)
  The primary mathematical and conceptual reference for this project. Covers the full ray tracing pipeline from scratch: ray construction, sphere intersections, Lambertian shading, camera setup. Served as the theoretical foundation for the mandatory part.

- [The Cherno — Ray Tracing Series (YouTube)](https://www.youtube.com/watch?v=Qz0KTGYJtUk&list=PLFt_AvWsXl0dlgwe4JQ0oZuleqOTjmox3)
  Practical video series implementing a ray tracer step by step. Referenced for architecture decisions and real-time rendering approaches.

- [occoccoc — Ray Tracing Series (YouTube)](https://youtube.com/playlist?list=PLAqGIYgEAxrUO6ODA0pnLkM2UOijerFPv)
  Complementary series covering additional intersection and lighting techniques.

**Textures**

- [Solar System Scope — Free Textures](https://www.solarsystemscope.com/textures/)
  Source of all planet, sun, and star field textures used in the solar simulation. Available in 2K and 8K resolution.

**Mathematics & Theory**

Wikipedia was used extensively for mathematical definitions and formulas, including: [Phong reflection model](https://en.wikipedia.org/wiki/Phong_reflection_model), [Verlet integration](https://en.wikipedia.org/wiki/Verlet_integration), [UV mapping](https://en.wikipedia.org/wiki/UV_mapping), [Bump mapping](https://en.wikipedia.org/wiki/Bump_mapping), [N-body simulation](https://en.wikipedia.org/wiki/N-body_simulation), [Line–sphere intersection](https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection).

**AI Usage**

AI assistants (ChatGPT, GitHub Copilot) were used during development for:
- Generating repetitive boilerplate code (parsing validators, error message structures)
- Finding and verifying mathematical equations (UV sphere mapping, bump map gradient estimation, gravitational constant scaling in AU/day units)
- Guidance on good implementation practices (shadow acne epsilon offset, Verlet energy conservation, Phong specular clamping)
- Debugging assistance on specific edge cases (cylinder cap intersections, UV wrapping artifacts)

All suggestions from AI tools were reviewed, understood, and integrated manually by the authors.*This project has been created as part of the 42 curriculum by <pchazalm>, <rcompain>.*

<div align="center">

```
███╗   ███╗██╗███╗   ██╗██╗██████╗ ████████╗
████╗ ████║██║████╗  ██║██║██╔══██╗╚══██╔══╝
██╔████╔██║██║██╔██╗ ██║██║██████╔╝   ██║   
██║╚██╔╝██║██║██║╚██╗██║██║██╔══██╗   ██║   
██║ ╚═╝ ██║██║██║ ╚████║██║██║  ██║   ██║   
╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝   ╚═╝   
```

*A ray tracer written in C — from scratch, pixel by pixel.*

[![Language](https://img.shields.io/badge/language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Platform](https://img.shields.io/badge/platform-Linux-lightgrey.svg)](https://www.linux.org/)
[![Library](https://img.shields.io/badge/graphics-MacroLibX-orange.svg)](https://github.com/Tabrizian/MacroLibX)

</div>

---

## Table of Contents

- [Description](#description)
- [Features](#features)
  - [Mandatory](#mandatory)
  - [Bonus](#bonus)
  - [Solar Mode (.solar)](#solar-mode-solar)
- [How Ray Tracing Works](#how-ray-tracing-works)
  - [The Ray](#the-ray)
  - [Intersections](#intersections)
  - [Lighting Model (Phong)](#lighting-model-phong)
  - [Shadows](#shadows)
  - [Textures & UV Mapping](#textures--uv-mapping)
  - [Bump Mapping](#bump-mapping)
  - [Gamma Correction](#gamma-correction)
- [Physics Simulation (Verlet)](#physics-simulation-verlet)
- [Instructions](#instructions)
  - [Dependencies](#dependencies)
  - [Compilation](#compilation)
  - [Execution](#execution)
  - [Controls](#controls)
- [Scene File Formats](#scene-file-formats)
  - [Mandatory .rt Format](#mandatory-rt-format)
  - [Bonus .rt Format](#bonus-rt-format)
  - [Solar .solar Format](#solar-solar-format)
- [Screenshots](#screenshots)
- [Resources](#resources)

---

## Description

**MiniRT** is a ray tracer built entirely from scratch in C as part of the 42 school curriculum. It renders 3D scenes described in plain-text files (`.rt` or `.solar`) by simulating the physical behavior of light rays.

The project comes in three versions of increasing complexity:

| Mode | Command | Description |
|------|---------|-------------|
| Mandatory | `make` | Basic ray tracer: spheres, planes, cylinders, ambient + diffuse lighting |
| Bonus | `make bonus` | Full Phong lighting, hard shadows, textures (image map + bump map + chessboard), interactive camera |
| Solar | `make bonus` + `.solar` file | N-body gravitational simulation using Verlet integration, rendered in real-time with texture-mapped planets |

The graphics window is provided by **MacroLibX**, a custom lightweight graphics library written in C++ using Vulkan, developed specifically for 42 projects on Linux.

---

## Features

### Mandatory

- **3 geometric primitives**: sphere, infinite plane, cylinder
- **Camera**: configurable position, orientation, and horizontal field of view (FOV)
- **Ambient light**: uniform background illumination
- **Point light**: one positional light source with intensity and color
- **Diffuse (Lambertian) shading**: light intensity proportional to the angle of incidence
- **Scene parsing**: custom `.rt` file format with strict validation and descriptive error messages
- **Interactive camera**: real-time navigation with keyboard
- **resize and moove**: real-time resize and moove objects with R

### Bonus

Everything in Mandatory, plus:

- **Specular highlights** (Phong reflection model): shiny reflections on surfaces
- **Hard shadows**: shadow rays detect occlusion between the hit point and the light source
- **Image textures**: PNG texture mapping on spheres, planes, and cylinders using UV coordinates
- **Bump mapping**: normal perturbation using a grayscale height map for surface detail illusion
- **Chessboard texture**: procedural alternating two-color pattern on any primitive
- **Gamma correction**: perceptual color correction applied to the final pixel color
- **Physics simulation**: N-body gravitational simulation (see Solar Mode)

### Solar Mode (.solar)

A special extension of the bonus mode activated when a `.solar` file is provided. Each sphere can optionally be given a **mass** (in solar masses) and an **initial velocity vector**.

At runtime, the gravitational attraction between all physics-enabled bodies is computed at every frame and their positions are updated via **Verlet integration** (60 sub-steps per frame). This allows simulating planetary systems such as our Solar System with physically plausible orbits.

Units used internally:
| Quantity | Unit |
|----------|------|
| Distance | 1 AU (Astronomical Unit = 1.496×10¹¹ m) |
| Mass | 1 Solar mass (1.989×10³⁰ kg) |
| Time | 1 day (86400 s) |

Pre-built maps are provided.
---

## How Ray Tracing Works

Ray tracing is a rendering technique that simulates light by casting rays from the camera into the scene and computing what each ray hits — the inverse of how light physically works (from light sources to the eye).

### The Ray

For each pixel `(x, y)` on the screen, a ray is constructed:

```
ray.origin = camera.origin
ray.direction = normalize(viewport_corner + x * horizontal_vec + y * vertical_vec - camera.origin)
```

The viewport is built from the camera's FOV and the aspect ratio of the window:

```
focal = 1 / tan(fov / 2)
horizontal_vec = right_vector * aspect_ratio
vertical_vec   = up_vector
corner         = forward * focal - horizontal_vec/2 - vertical_vec/2
```

All rays are normalized before use to guarantee consistent distance calculations.

### Intersections

For each ray, every object in the scene is tested. The closest positive intersection (`t > 0.001`) is kept.

#### Sphere

A sphere of center **C** and radius **r** is hit when:

```
||ray(t) - C||² = r²
```

Expanding with `ray(t) = O + t*D` and `oc = O - C`:

```
a = D·D
b = oc·D
c = oc·oc - r²
discriminant = b² - a*c

t = (-b - sqrt(discriminant)) / a   (nearest root)
```

If `discriminant < 0` → no intersection. If the nearest `t` is behind the camera (negative), the far root is tested.

#### Plane

A plane defined by a point **P** and normal **N** intersects at:

```
t = ((P - O) · N) / (D · N)
```

If `D · N ≈ 0` the ray is parallel to the plane (no intersection).

#### Cylinder

The cylinder (axis **v**, center **C**, radius **r**, height **h**) requires separating the ray into components parallel and perpendicular to the axis:

```
A_vec = D - (D·v)*v        // D projected onto plane perpendicular to axis
B_vec = oc - (oc·v)*v      // oc projected similarly

a = A_vec · A_vec
b = A_vec · B_vec
c = B_vec · B_vec - r²
```

After solving the quadratic, the hit point is checked to be within `[-h/2, h/2]` along the axis. The two flat **caps** are tested independently as disk-plane intersections.

### Lighting Model (Phong)

The Phong model decomposes light into three components:

```
I = ambient + diffuse + specular
```

#### Ambient

```
ambient[c] = (ambient_color[c] / 255) * ambient_ratio
```

Always present regardless of geometry.

#### Diffuse (Lambertian)

```
coef_diffuse = dot(N, L)          // N = surface normal, L = direction to light
diffuse[c]   = (light_color[c] / 255) * coef_diffuse * light_intensity
```

Only applied if `coef_diffuse > 0` (surface faces the light) and no shadow occlusion.

#### Specular (Phong)

```
R = 2 * (N·L) * N - L            // reflection vector
coef_specular = dot(R, V)         // V = direction to camera
specular[c] = (light_color[c] / 255) * pow(coef_specular, SHININESS) * KS * intensity
```

Constants used: `SHININESS = 32`, `KS = 0.5`.

Only applied when `coef_specular > EPS`.

#### Final composition

```
light[c] = clamp(ambient[c] + diffuse[c] + specular[c], 0.0, 1.0)
pixel_color[c] = 255 * pow(object_color[c] * light[c] / 255, GAMMA)
```

### Shadows

After finding a hit point, a **shadow ray** is cast from the hit point toward the light source:

```
shadow_ray.origin    = hit_point + 0.001 * normal    // small offset to avoid self-intersection
shadow_ray.direction = normalize(light_position - hit_point)
```

The scene is tested for any intersection along this ray with `t < distance_to_light`. If found, the point is in shadow — diffuse and specular components are zeroed.

The `0.001` epsilon offset is critical to prevent **shadow acne** (a surface incorrectly self-shadowing due to floating-point imprecision).

### Textures & UV Mapping

In bonus mode, a texture image (PNG) can be mapped onto any primitive by computing **(u, v)** coordinates at the hit point — normalized coordinates in [0, 1] that indicate where in the image to sample.

#### Sphere UV

```
u = 0.5 + atan2(Pz, Px) / (2π)
v = 0.5 + asin(Py) / π
```

where `(Px, Py, Pz)` is the normalized hit point relative to the sphere center.

#### Plane UV

Two orthogonal tangent vectors are computed from the plane normal:

```
tangent   = cross(normal, up)    // (fallback to 'depth' if normal ≈ up)
bitangent = cross(normal, tangent)
u = dot(hit_point, tangent)
v = dot(hit_point, bitangent)
```

#### Cylinder UV

The lateral surface uses the angle around the axis for `u` and the projection along the axis for `v`. Caps use the same tangent/bitangent method as the plane.

#### Chessboard

Instead of sampling an image, the UV index is computed:

```
case_idx = floor(u / scale) + floor(v / scale)
color = (case_idx % 2 == 0) ? color1 : color2
```

### Bump Mapping

Bump mapping perturbs the surface **normal** at a hit point to simulate fine surface relief without modifying geometry. A grayscale height map image is used.

For a hit point with UV coordinates `(u, v)`, the gradient is estimated by finite differences:

```
h        = luminance(bump_map(u,     v))
h_next_u = luminance(bump_map(u+du,  v))
h_next_v = luminance(bump_map(u,     v+dv))

gradient_u = h_next_u - h
gradient_v = h_next_v - h
```

where `luminance = (r + g + b) / (3 * 255)`.

The normal is then perturbed along the tangent and bitangent vectors:

```
new_normal = normalize(normal + gradient_u * tangent + gradient_v * bitangent)
```

This creates the illusion of bumps and ridges on the surface.

### Gamma Correction

Human vision perceives brightness non-linearly. Without correction, dark tones appear too dark on screen. A gamma of **0.8** is applied after lighting:

```
final_color[c] = 255 * pow(lit_color[c] / 255, GAMMA)    // GAMMA = 0.8
```

---

## Physics Simulation (Verlet)

The solar mode uses **Verlet integration** to update the position of each physics-enabled body each frame. Unlike Euler integration, Verlet does not require storing velocity explicitly — it is implicitly encoded in the difference between the current and previous positions, making it **more numerically stable** over long simulations.

### Position Update

```
new_pos = 2 * cur_pos - prev_pos + acc * dt²
```

After the update, `prev_pos ← cur_pos` and `cur_pos ← new_pos`.

### Acceleration (Gravitational N-body)

For each pair of bodies `(i, j)`:

```
dir  = normalize(pos_j - pos_i)
dist = ||pos_j - pos_i||

acc_i += G * m_j / dist² * dir
acc_j -= G * m_i / dist² * dir
```

Pairs with `dist < 0.001` are skipped to avoid singularities (collision/merger condition).

The gravitational constant is scaled to the AU/solar_mass/day unit system:

```
G = 2.959122e-4    (AU³ / (solar_mass * day²))
DT = 0.01          (days per step)
```

### Simulation Speed

60 Verlet steps are executed per rendered frame, meaning each visual frame represents `60 * DT = 0.6` simulated days.

---

## Instructions

### Dependencies

MiniRT uses **MacroLibX** (included as a submodule) which requires:

```bash
# Ubuntu / Debian
sudo apt-get install build-essential cmake libvulkan-dev libx11-dev libxext-dev

# Arch Linux
sudo pacman -S base-devel cmake vulkan-headers libx11 libxext
```

> **Note:** A Vulkan-compatible GPU driver is required. On VMs, ensure Vulkan support is enabled.

### Compilation

```bash
# Clone the repository (with submodules)
git clone --recurse-submodules https://github.com/Remi-cpn/MiniRT.git
cd MiniRT

# Build MacroLibX first (done automatically by the Makefile)
# Compile mandatory version
make

# Compile bonus version (textures, bump maps, physics)
make bonus

# Clean objects
make clean

# Full clean (objects + binary)
make fclean

# Rebuild
make re
```

> The Makefile automatically selects the correct source directory (`Mandatory/` or `Bonus/`) based on the build target.

### Execution

```bash
# Mandatory
./minirt path/to/scene.rt

# Bonus (standard .rt file)
./minirt path/to/scene.rt

# Bonus (solar simulation)
./minirt path/to/scene.solar
```

Example scenes are provided in `Mandatory/maps/` and `Bonus/maps/`.

```bash
# Quick test examples
./minirt Mandatory/maps/basic.rt
./minirt Bonus/maps/solar_system.solar
./minirt Bonus/maps/Double_sun.solar
./minirt Bonus/maps/with_mune.solar
```

> The program detects the `.solar` extension automatically and activates the physics simulation accordingly.

### Controls

| Key | Action |
|-----|--------|
| `ESC` | Quit the program |
| `W` | Move camera forward |
| `S` | Move camera backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `SPACE` | Move camera up |
| `CTRL` | Move camera down |
| `↑` | Rotate camera up (pitch) |
| `↓` | Rotate camera down (pitch) |
| `←` | Rotate camera left (yaw) |
| `→` | Rotate camera right (yaw) |
| `I` | Increase FOV |
| `O` | Decrease FOV |
| `R` | Reload scene from file |
| ✕ (window close) | Quit the program |

> **Note:** CTRL and SPACE are currently bound but partially unused in the update logic — camera vertical movement is active. R reloads and reparses the `.rt` file on the fly without restarting.

---

## Scene File Formats

All scene files use **space-separated fields** on each line. Lines beginning with `#` are comments (bonus only). Each identifier must appear **exactly once** for `A`, `C`, and `L`. Objects (`sp`, `pl`, `cy`) can be repeated freely.

### Mandatory .rt Format

| Identifier | Fields | Description |
|------------|--------|-------------|
| `A` | `ratio R,G,B` | Ambient light. `ratio` ∈ [0.0, 1.0] |
| `C` | `x,y,z dx,dy,dz fov` | Camera. Direction must be normalized. `fov` ∈ ]0, 180[ |
| `L` | `x,y,z intensity R,G,B` | Point light. `intensity` ∈ [0.0, 1.0] |
| `sp` | `x,y,z diameter R,G,B` | Sphere |
| `pl` | `x,y,z nx,ny,nz R,G,B` | Plane. Normal must be normalized |
| `cy` | `x,y,z ax,ay,az diameter height R,G,B` | Cylinder. Axis must be normalized |

**Example:**
```
A 0.2 255,255,255
C 0,0,-5 0,0,1 70
L 2,3,-2 0.8 255,255,255
sp 0,0,3 1.0 255,0,0
pl 0,-1,0 0,1,0 100,100,100
cy 2,0,3 0,1,0 0.5 2.0 0,0,255
```

> Colors are in `R,G,B` format with values ∈ [0, 255]. Vectors use `x,y,z` with comma separators (no spaces). Diameters (not radii) are given for spheres and cylinders — the parser divides by 2 internally.

---

### Bonus .rt Format

Same as Mandatory, with **optional texture/chessboard fields** appended to objects:

| Object | Full format |
|--------|-------------|
| `sp` | `x,y,z diameter R,G,B [texture.png [bump.png]]` |
| `sp` | `x,y,z diameter R,G,B [scale R2,G2,B2]` ← chessboard |
| `pl` | `x,y,z nx,ny,nz R,G,B [texture.png [bump.png]]` |
| `pl` | `x,y,z nx,ny,nz R,G,B [scale R2,G2,B2]` ← chessboard |
| `cy` | `x,y,z ax,ay,az diameter height R,G,B [texture.png [bump.png]]` |
| `cy` | `x,y,z ax,ay,az diameter height R,G,B [scale R2,G2,B2]` ← chessboard |

- **Texture**: path to a PNG file, relative to the binary's working directory
- **Bump map**: optional second PNG, used as a grayscale height map for normal perturbation
- **Chessboard**: `scale` is a float > 0 (tile size). A second color `R2,G2,B2` is required

The parser distinguishes between texture and chessboard by checking whether the 4th field parses as a valid `double` (chessboard scale) or not (texture path).

**Examples:**
```
# Sphere with image texture
sp 0,0,3 2.0 255,255,255 texture_map/2k_earth.png

# Sphere with texture + bump map
sp 0,0,3 2.0 255,255,255 texture_map/moon.png texture_map/moon_bump.png

# Plane with chessboard (scale 1.0, alternating white and black)
pl 0,-1,0 0,1,0 255,255,255 1.0 0,0,0

# Cylinder with texture
cy 0,0,2 0,1,0 1.0 3.0 200,200,200 texture_map/metal.png
```

---

### Solar .solar Format

Used exclusively with `make bonus`. The file extension `.solar` is detected at runtime to activate the physics simulation.

The `A`, `C`, and `L` fields are identical to the Bonus `.rt` format.

Objects are exclusively **spheres** with the following format:

```
sp x,y,z diameter R,G,B texture.png [mass vx,vy,vz]
```

| Field | Description |
|-------|-------------|
| `x,y,z` | Initial position in AU |
| `diameter` | Visual diameter (AU) |
| `R,G,B` | Fallback color if no texture |
| `texture.png` | Path to texture image (required) |
| `mass` | Mass in solar masses (e.g. `3.003e-6` for Earth). **Omit to make the body static** |
| `vx,vy,vz` | Initial velocity vector (AU/day). Required if mass is set |

**Example** (excerpt from `solar_system.solar`):
```
A 0.2 255,255,255
C 0,1,2 0,-0.3,-1 70
L 0,0,3 0.8 255,255,255

# Sun (static, mass given but velocity 0)
sp 0,0,0 0.5 255,255,0 texture_map/2k_sun.png 1.0 0,0,0

# Earth
sp 1,0,0 0.05 100,150,255 texture_map/2k_earth.png 3.003e-6 0,0.0172,0

# Mars
sp 1.524,0,0 0.03 255,100,80 texture_map/2k_mars.png 3.21e-7 0,0.0139,0
```

> Texture files for the Solar System are sourced from [Solar System Scope](https://www.solarsystemscope.com/textures/) and must be placed in a `texture_map/` folder relative to the binary.

---

## Screenshots

> *(Add screenshots here)*

<!-- 
Example:
![Solar System](screenshots/solar_system.png)
![Bump Mapped Sphere](screenshots/bump_map.png)
![Chessboard Scene](screenshots/chessboard.png)
![Shadow Test](screenshots/shadows.png)
-->

---

## Resources

### Ray Tracing

- [**Ray Tracing in One Weekend** — Peter Shirley](https://raytracing.github.io/books/RayTracingInOneWeekend.html)  
  The foundational resource for this project. Covers the core ray tracing pipeline: rays, sphere intersections, Lambertian shading, and camera setup. Used as the primary mathematical and conceptual reference.

- [**The Cherno — Ray Tracing Series** (YouTube)](https://www.youtube.com/watch?v=Qz0KTGYJtUk&list=PLFt_AvWsXl0dlgwe4JQ0oZuleqOTjmox3)  
  Practical video series implementing a ray tracer step by step in C++. Used for understanding real-time rendering architecture and implementation decisions.

- [**Ray Tracing Series by occoccoc** (YouTube)](https://youtube.com/playlist?list=PLAqGIYgEAxrUO6ODA0pnLkM2UOijerFPv)  
  Complementary video series covering additional techniques. Referenced for alternative approaches to intersection algorithms and lighting.

### Textures

- [**Solar System Scope — Free Textures**](https://www.solarsystemscope.com/textures/)  
  Source of all planet, sun, and star field texture maps used in the solar simulation mode. High-resolution 2K and 8K PNG images for all Solar System bodies.

### Mathematics & Algorithms

- **Wikipedia** — Used extensively for mathematical formulas and theoretical concepts, including:
  - [Phong reflection model](https://en.wikipedia.org/wiki/Phong_reflection_model)
  - [Verlet integration](https://en.wikipedia.org/wiki/Verlet_integration)
  - [UV mapping](https://en.wikipedia.org/wiki/UV_mapping)
  - [Bump mapping](https://en.wikipedia.org/wiki/Bump_mapping)
  - [Gravitational N-body problem](https://en.wikipedia.org/wiki/N-body_problem)
  - [Specular highlight](https://en.wikipedia.org/wiki/Specular_highlight)
  - [Ray–sphere intersection](https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection)

### AI Usage

AI assistants (ChatGPT, GitHub Copilot) were used during development for the following tasks:

- **Repetitive/boilerplate code**: generating utility function skeletons, error message structures, and parsing validation patterns
- **Mathematical equations**: deriving and verifying formulas for UV sphere mapping, bump map gradient estimation, Verlet integration in astronomical units, and the scaling of the gravitational constant G
- **Implementation best practices**: guidance on avoiding shadow acne (normal offset epsilon), numerical stability in the physics integrator, and correct Phong specular clamping
- **Debugging assistance**: identifying edge cases in the cylinder cap intersection logic and UV coordinate wrapping artifacts

All AI-generated suggestions were reviewed, understood, and adapted by the authors before integration into the codebase.
