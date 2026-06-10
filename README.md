# BMCC Cafeteria Food Impact

A desktop application, built with **Qt and C++**, that shows BMCC students the
environmental footprint of cafeteria food and suggests greener choices.

**Author:** Ramim Hussain (ID: 24718712)
**Course:** CSC211H Honors — Spring 2026

---

## What it does

Every item on the BMCC cafeteria menu is rated by its environmental impact using
real data from **Poore & Nemecek (2018)**. The app lets a student:

- **Browse the menu** by category (Breakfast, Lunch, Pizza, BBQ, Snacks, Entrees,
  Desserts, Beverages).
- **See an item's impact** — its carbon, water, or land footprint, a
  Low / Medium / High label, and a colored impact meter.
- **Switch the metric** — view impact by carbon, water, or land use; the same
  items rank differently depending on the metric chosen.
- **Get a greener pick** — high-impact items suggest a lower-carbon alternative
  from the same category.
- **Compare two items** side by side to see which has the larger footprint.

## The goal

Food is one of the largest drivers of greenhouse-gas emissions, but cafeteria
menus never show that. A beef burger can emit roughly **99x** more CO2 than a
veggie burger, yet nothing signals that at the point of choice. This app puts
that information in front of students and nudges them toward better options —
small daily swaps that, across thousands of students, add up to a real
reduction in emissions.

## How the code is organized

The project separates **logic** (plain C++) from the **interface** (Qt):

### Logic layer
- **EnvironmentalImpact** — base class storing an item's CO2, water, and land
  values; computes a 0–10 impact score and a Low/Medium/High label.
- **WaterImpact / LandImpact** — subclasses that inherit from
  EnvironmentalImpact and **override** the scoring to rank by water or land
  instead of carbon (demonstrates inheritance and polymorphism).
- **MenuItem** — one food item: name, price, category, and its impact.
- **MenuDatabase** — loads all items from `menu.json` and stores them.
- **ImpactCalculator** — ranks items, suggests swaps, and compares two items.

### Interface layer
- **mainwindow** — the Qt window: Home, Menu, and Compare pages, the impact-type
  toggle, the meter, and the comparison tool.
- **main.cpp** — starts the app and applies the dark theme.

### Data
- **menu.json** — the 38 BMCC items with their carbon, water, and land data.
- **resources.qrc** — bundles `menu.json` into the executable.

## Data source

Poore, J., & Nemecek, T. (2018). *Reducing food's environmental impacts through
producers and consumers.* Science, 360(6392), 987–992.

## How to build and run

1. Open `BMCCFoodImpact.pro` in Qt Creator.
2. Select a Desktop Qt kit when prompted.
3. Press Run.
