ansi
=============================================

A modern C++23 library for beautiful terminal styling.

.. code-block:: cpp

   #include "ansi.h++"
   using namespace nutsloop;

   std::cout << "Hello"_.red().bold() << " " << "World"_.green().underline() << std::endl;

.. toctree::
   :maxdepth: 2
   :caption: Contents

   overview
   installation
   quick_start
   colors
   styles
   hyperlinks
   advanced
   terminal
   requirements
