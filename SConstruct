env = Environment()
env['CPPPATH'] = [ './inc', './depends/tetra-meta/inc' ]
env['LIBPATH'] = [ './bin', './depends/tetra-meta/bin' ]
env['LIBS'] = [ 'tetraMeta' ]
env['CXX'] = 'clang++';
env['CXXFLAGS'] = "-std=c++11"

buildLib = env.Library('./bin/tetraMessage', Glob('src/*/*/*.cpp'))

env['CPPPATH'] += ['./tst']
env['LIBS'] += [ 'tetraMessage' ]
buildTests = env.Program('./bin/catchTests.out', 
                         Glob('tst/*.cpp') + Glob('tst/*/*/*.cpp'));
Depends(buildTests, buildLib)

runTests = Command( target = "runTests"
                  , source = "./bin/catchTests.out"
                  , action = [ "./bin/catchTests.out" ]
                  )

Depends(runTests, buildTests)
Default(runTests)
