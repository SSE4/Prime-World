add_library(MayaExtension EXCLUDE_FROM_ALL
bindFile/BNFL.cpp
bindFile/BNFL.h
bindFile/reader.cpp
bindFile/readerIDX.cpp
bindFile/writer.cpp
bindFile/writerBlind.cpp
bindFile/writerIDX.cpp
blindDataShader/blindDataMesh.cpp
blindDataShader/blindDataMesh.h
cvColorShader/CVCS.cpp
h6export/Anim.cpp
h6export/Anim.h
h6export/Debug.cpp
h6export/H6EX.cpp
h6export/H6EX.h
h6export/Lght.cpp
h6export/Part.cpp
h6export/Part.h
h6export/Skel.cpp
h6export/Skin.cpp
h6export/Stat.cpp
h6export/Write.cpp
helloWorld/HLWD.cpp
helloWorld/HLWD.h
mapFaces/MPFS.cpp
polyTrace/PTRC.cpp
setVertexNormals/VNRM.cpp
displace/DSPL.cpp
displace/DSPL.h
commandClasses.h
libs.h
plugin.cpp
)
target_include_directories(MayaExtension PRIVATE ${SRCROOT})
target_compile_definitions(MayaExtension PRIVATE "-D_SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS=1")
target_link_libraries(MayaExtension PRIVATE maya)
