import pyjet


pyjet.Logging.mute()
res_x = 50
res = (res_x, res_x * 2, res_x)
size_x = 1
voxel_size = size_x / res_x
grid_spacing = (voxel_size, voxel_size, voxel_size)
origin = (0, 0, 0)
number_of_frames = 300
fps = 60
solver = pyjet.LevelSetLiquidSolver3(res, grid_spacing, origin)
grids = solver.gridSystemData
domain = grids.boundingBox
plane = pyjet.Plane3(
    (0, 1, 0),    # normal
    (0, 0.25 * domain.height, 0),    # point
)
sphere = pyjet.Sphere3(
    domain.midPoint(),    # center
    domain.width * 0.15    # radius
)
surface_set = pyjet.SurfaceSet3([plane, sphere])
emitter = pyjet.VolumeGridEmitter3(surface_set)
solver.emitter = emitter
emitter.addSignedDistanceTarget(solver.signedDistanceField)
frame = pyjet.Frame(0, 1 / fps)
for frame_index in range(number_of_frames):
    print('frame {:0>3}'.format(frame_index))
    solver.update(frame)
    surface_mesh = pyjet.marchingCubes(
        solver.signedDistanceField,
        grid_spacing,
        origin,
        0,    # iso value
        pyjet.DIRECTION_ALL,
        pyjet.DIRECTION_NONE
    )
    surface_mesh.writeObj('frame_{:0>3}.obj'.format(frame_index))
    frame.advance()
