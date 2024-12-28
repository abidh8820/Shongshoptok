# Notebook Generator

A tool for generating team notebooks with customizable formatting options.

## Requirements

### Ubuntu/Debian
```bash
# Install Python 3
sudo apt-get install python3

# Install LaTeX packages
sudo apt-get install texlive-latex-base texlive-latex-recommended texlive-latex-extra texlive-fonts-recommended texlive-luatex

# Install PDF viewer
sudo apt-get install zathura
```

## Usage
```bash
bash generate.sh
```

The script will prompt you with several configuration options:

### Configuration Options

1. **Load Saved Data**
   - Yes: Load previously saved configuration
   - No: Start with fresh configuration

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

## Troubleshooting

If you encounter LaTeX parsing errors, check that:
- Team name contains no underscores (use spaces instead)
- University name contains no underscores (use spaces instead)
- All required LaTeX packages are installed

## Output
The generated notebook will be saved as `team-notebook.pdf` in your current directory.
