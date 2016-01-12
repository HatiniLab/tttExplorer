cmake_minimum_required(VERSION 2.8)

if(POLICY CMP0020)
  cmake_policy(SET CMP0020 NEW)
endif()

PROJECT(tttExplorer)
add_definitions("-std=c++11 -fpermissive -Wno-static-float-init")
set(CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

find_package(VTK 6.3 COMPONENTS
  vtkCommonCore
  vtkFiltersCore
  vtkInfovisCore
  vtkInteractionStyle

  #vtkRenderingFreeType${VTK_RENDERING_BACKEND}
  #vtkRenderingVolume${VTK_RENDERING_BACKEND}
  vtkRenderingVolume
  vtkRenderingVolumeOpenGL
  vtkViewsQt
  
  vtkjsoncpp
  vtkChartsCore
  #vtkRenderingContext${VTK_RENDERING_BACKEND}
  vtkViewsContext2D
  #vtkIOFFMPEG

)

include(${VTK_USE_FILE})

if(${VTK_VERSION} VERSION_GREATER "6" AND VTK_QT_VERSION VERSION_GREATER "4")
  # Instruct CMake to run moc automatically when needed.
  set(CMAKE_AUTOMOC ON)
  find_package(Qt5Widgets REQUIRED QUIET)
else()
  find_package(Qt4 REQUIRED)
  include(${QT_USE_FILE})
endif()

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ./Drawers/
)
include_directories(/home/morgan/Tracker/tttrelease/ttt/Modules/DataStorage/include)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

set( Srcs main.cpp tttexplorermainwindow.cpp tttlayermanager.cpp ttttimelapsemanager.cpp tttlayermodel.cpp tttnewprojectdialog.cpp tttaddimagelayerdialog.cpp)

set( Hdrs )

set( MOC_Hdrs tttexplorermainwindow.h tttlayermanager.h ttttimelapsemanager.h tttlayermodel.h tttnewprojectdialog.h tttaddimagelayerdialog.h)

set( UIs tttexplorermainwindow.ui tttlayermanager.ui ttttimelapsemanager.ui tttnewprojectdialog.ui tttaddimagelayerdialog.ui)

#set( QRCs Icons/icons.qrc )


# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

if(${VTK_VERSION} VERSION_GREATER "6" AND VTK_QT_VERSION VERSION_GREATER "4")
  qt5_wrap_ui(UISrcs ${UIs}  )
  # CMAKE_AUTOMOC in ON so the MOC headers will be automatically wrapped.
  add_executable(tttExplorer MACOSX_BUNDLE ${Srcs} ${Hdrs} ${UISrcs} ${MOC_Hdrs}  )
  qt5_use_modules(tttExplorer Core Gui Widgets)
  target_link_libraries(tttExplorer ${VTK_LIBRARIES} ${ITK_LIBRARIES} vtkGUISupportQt vtkRenderingVolume vtkRenderingVolumeOpenGL jsoncpp)
else()
  QT4_WRAP_UI(UISrcs ${UI_FILES})
  QT4_WRAP_CPP(MOCSrcs ${QT_WRAP})
  add_executable(tttExplorer MACOSX_BUNDLE ${CXX_FILES} ${UISrcs} ${MOCSrcs})

  if(VTK_LIBRARIES)
    if(${VTK_VERSION} VERSION_LESS "6")
      target_link_libraries(tttExplorer ${VTK_LIBRARIES} QVTK)
    else()
      target_link_libraries(tttExplorer ${VTK_LIBRARIES})
    endif()
  else()
    target_link_libraries(tttExplorer vtkHybrid QVTK vtkViews ${QT_LIBRARIES})
  endif()
endif()
