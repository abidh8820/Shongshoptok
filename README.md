# Notebook Generator

A tool for generating team notebooks with customizable formatting options.

## Project Structure
```
notebook/
├── codes/          # Most for your ncessary codes will be here, should be foldered according to category
├── extra/          # Additional content like build files
```

The notebook will automatically generate a table of contents based on your folder structure. The hierarchy of your folders in `codes/` and `extra/` will be reflected in the final PDF's table of contents.

For example:
```
codes/
├── data_structures/
│   ├── segment_tree.cpp
│   └── fenwick_tree.cpp
└── graphs/
    ├── dijkstra.cpp
    └── floyd_warshall.cpp
```
Will generate a corresponding hierarchical table of contents in the PDF.

## Requirements

### Ubuntu/Debian
```bash
# Install Python 3
sudo apt-get install python3

# Install LaTeX packages
sudo apt-get install texlive-latex-base texlive-latex-recommended texlive-latex-extra texlive-fonts-recommended texlive-luatex
or 
#if something breaks or you have good bandwith
sudo apt-get install texlive-full


# Install PDF viewer
sudo apt-get install zathura
```

## Usage
```bash
cd notebook
bash generate.sh
```

The script will prompt you with several configuration options:

### Configuration Options

1. **Load Saved Data**
   - Yes: Load previously saved configuration
   - No: Start with fresh configuration // you should be using this for the first time

2. **Team Information**
   - Enter your team name
   - Enter your university/institution name
   
   ⚠️ Important: Use spaces instead of underscores (_) in team and university names
   ```
   ✅ Correct: "Team Name"
   ❌ Incorrect: "Team_Name"
   
   ✅ Correct: "Islamic University of Technology"
   ❌ Incorrect: "Islamic_University_of_Technology"
   ```

3. **Layout Options**
   - Number of Columns:
     - 2 Columns
     - 3 Columns

4. **Page Orientation**
   - Portrait
   - Landscape

5. **Font Size**
   - 9pt
   - 10pt
   - 11pt
   - 12pt

After configuring these options, the script will:
1. Generate your notebook PDF
2. Automatically open it in Zathura for preview

## Content Organization
- Place your code files in the `codes/` directory
- Place additional content in the `extra/` directory
- Organize files in subdirectories to create sections in the table of contents
- The notebook will automatically generate a table of contents based on your folder structure

## Troubleshooting

If you encounter LaTeX parsing errors, check that:
- Team name contains no underscores (use spaces instead)
- University name contains no underscores (use spaces instead)
- All required LaTeX packages are installed
- Files are properly placed in `codes/` or `extra/` directories

## Output
The generated notebook will be saved as `team-notebook.pdf` in your current directory.
