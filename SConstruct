VariantDir('build', 'src', duplicate=0)

# Set our source files
source_files = Glob('src/*.cpp', 'src/*.h')

# Set our required libraries
libraries = []
# libraries = ['pthread']
library_paths = ''

env = Environment()

# Set our g++ compiler flags
env.Append( CPPFLAGS=['-std=c++11', '-Wall', '-g'] )

# Tell SCons the program to build
env.Program('build/PORR', source_files, LIBS = libraries, LIBPATH = library_paths)