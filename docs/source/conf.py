# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'Ansi library'
copyright = '2025, Simone Del Popolo'
author = 'Simone Del Popolo'
release = '1.0.1'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = [
    'myst_parser',
    'sphinx_copybutton',
]

source_suffix = {
    '.rst': 'restructuredtext',
    '.md': 'markdown',
}

templates_path = ['_templates']
exclude_patterns = []

# Enable MyST extensions if needed
myst_enable_extensions = [
    "colon_fence",  # ::: directives
    "deflist",  # Definition lists
    "linkify",  # Auto-link URLs
    "smartquotes",  # Fancy quotes
]

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'furo'
html_static_path = ['_static']

# Optional: Furo theme options
html_theme_options = {
    "sidebar_hide_name": True,
    "light_logo": "logo-light.png",
    "dark_logo": "logo-dark.png",
}
