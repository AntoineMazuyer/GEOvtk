#include <OGF/vtk/algo/vtk_io.h>
#include <geogram/mesh/mesh.h>

namespace vtk{
    class vtk_API VTKIOHandler : public GEO::MeshIOHandler {
        public:
        VTKIOHandler() {

        }

        virtual bool load(
            const std::string& filename, GEO::Mesh& M,
            const GEO::MeshIOFlags& ioflags
        ) {

        }

        virtual bool save(
            const GEO::Mesh& M, const std::string& filename,
            const GEO::MeshIOFlags& ioflags
        ) {

        }
    };

    void vtk_io_initialize() {
        geo_register_MeshIOHandler_creator(VTKIOHandler, "vtk");
    }
}
