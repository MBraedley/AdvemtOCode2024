from conan import ConanFile
import aocd
import os

class AdventOfCode2024(ConanFile):
    name = "AdventOfCode2024"
    version = "0.0.1"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        self.requires("ctre/[*]")
        self.requires("nlohmann_json/[*]")

    def generate(self):
        
        year = 2024
        for day in range(1, aocd.get.current_day() + 1 ):
            inputFileName = os.path.join( self.recipe_folder, "Day{:02d}".format(day), "input.txt" )
            print( inputFileName )
            fh = open( inputFileName, "w" )
            try:
                fh.write( aocd.get_data(day=day, year=year) )
            except:
                print(f"Couldn't get input data for day {day}")
            
    