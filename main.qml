import QtQuick 2.0
import QtQuick.Scene3D 2.0
import Qt3D.Render 2.15
import Qt3D.Core 2.0
import Qt3D.Input 2.0
import Qt3D.Extras 2.15


Item {
    function dtr(degrees)
    {
        return degrees*(Math.PI/180);
    }

    Rectangle {
        id: scene
        anchors.fill: parent
        color: "black"

        transform: Rotation {
            id: sceneRotation
            axis.x: 1
            axis.y: 0
            axis.z: 0
            origin.x: scene.width / 2
            origin.y: scene.height / 2
        }

        Scene3D {
            id: scene3d
            anchors.fill: parent
            focus: true
            aspects: ["input", "logic"]
            cameraAspectRatioMode: Scene3D.AutomaticAspectRatio

            Entity {
                id: sceneRoot

                Camera {
                    id: camera
                    objectName: "camera"
                    projectionType: CameraLens.PerspectiveProjection
                    fieldOfView: 90
                    aspectRatio: scene.width / scene.height
                    nearPlane: 0.1
                    farPlane: 1000.0
                    position: Qt.vector3d(0.0, 3.0, 2.0) //(_accX, _accY, _accZ)
                    viewCenter: Qt.vector3d(1000*Math.sin(dtr(_accX))*Math.cos(dtr(_accY)), 1000*Math.sin(dtr(_accX))*Math.sin(dtr(_accY)), 1000*Math.cos(dtr(_accX)))
                    //viewCenter: Qt.vector3d(_accX*0.1, _accY*0.1, 0.0)
                    upVector: Qt.vector3d(0.0, 1.0, 0.0)
                    }


                FirstPersonCameraController {
                    camera: camera
                }

                ShadowMapLight {
                    id: light
                }

                components: [
                    ShadowMapFrameGraph {
                        id: framegraph
                        viewCamera: camera
                        lightCamera: light.lightCamera
                    },
                    // Event Source will be set by the Qt3DQuickWindow
                    InputSettings { }
                ]


                AdsEffect {
                    id: shadowMapEffect

                    shadowTexture: framegraph.shadowTexture
                    light: light
                }

                // Trefoil knot entity
                Trefoil {
                    material: AdsMaterial {
                        effect: shadowMapEffect
                        specularColor: Qt.rgba(0.5, 0.5, 0.5, 1.0)
                    }
                }



                // Plane entity
                GroundPlane {
                    material: AdsMaterial {
                        effect: shadowMapEffect
                        diffuseColor: Qt.rgba(0.2, 0.5, 0.3, 1.0)
                        specularColor: Qt.rgba(0, 0, 0, 1.0)
                    }
                }
            }
        }
    }
}
