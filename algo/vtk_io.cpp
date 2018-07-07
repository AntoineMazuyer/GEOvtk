#include <OGF/GEOvtk/algo/vtk_io.h>
#include <geogram/mesh/mesh.h>

namespace GEOvtk{

    struct GEO2VTK {
        index_t entity_type;
        index_t vertices[8];
    };

    static GEO2VTK tet_descriptor_vtk = {
        10, // type
        { 0, 1, 2, 3 } // vertices
    };

    static GEO2VTK hex_descriptor_vtk = {
        12, // type
        { 0, 4, 5, 1, 2, 6, 7, 3 } // vertices
    };

    static GEO2VTK prism_descriptor_vtk = {
        13, // type
        { 0, 2, 1, 3, 5, 4 } // vertices
    };

    static GEO2VTK pyramid_descriptor_vtk = {
        14, // type
        { 0, 1, 2, 3, 4 } // vertices
    };

    static GEO2VTK* cell_type_to_cell_descriptor_vtk[4] = {
        &tet_descriptor_vtk, &hex_descriptor_vtk, &prism_descriptor_vtk,
        &pyramid_descriptor_vtk
    };

    class GEOvtk_API VTKIOHandler : public GEO::MeshIOHandler {
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
            bind_attributes(M, ioflags, false);

            std::ofstream out(filename.c_str());
            if( !out ) {
                GEO::Logger::err("I/O")
                    << "Could not create file : "
                    << filename
                    << std::endl;
                return false;
            }

            // Write file version
            out << "# GEOvtk DataFile Version 3.0\n";

            // Write Header
            out << "Mesh exported with Graphite\n";

            // This file is written in ASCII
            out << "ASCII\n";

            // We are dealing only with unstructured grid
            out << "DATASET UNSTRUCTURED_GRID \n";

            // Vertices export
            index_t dim = 3;
            out << "POINTS " << M.vertices.nb() << " double\n";
            for( index_t v = 0; v < M.vertices.nb(); ++v ) {
                out << M.vertices.point(v) << "\n";
            }

            // Elements export - Total number of elements
            index_t total_elements_nb = 0;
            index_t total_vertices_nb = ( 2 + 1 ) * M.edges.nb()
                + ( 3 + 1 ) * M.facets.nb_triangles();
                + ( 4 + 1 ) * M.facets.nb_quads();
            if( ioflags.has_element( GEO::MESH_EDGES ) ) {
                total_elements_nb += M.edges.nb();
            }
            if( ioflags.has_element( GEO::MESH_FACETS ) ) {
                total_elements_nb += M.facets.nb();
            }
            if( ioflags.has_element( GEO::MESH_CELLS ) ) {
                total_elements_nb += M.cells.nb();
            }
            out.close();


        }
    };

    void GEOvtk_io_initialize() {
        geo_register_MeshIOHandler_creator(VTKIOHandler, "vtk");
    }
}
