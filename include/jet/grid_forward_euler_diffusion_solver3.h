// Copyright (c) 2016 Doyub Kim

#ifndef INCLUDE_JET_GRID_FORWARD_EULER_DIFFUSION_SOLVER3_H_
#define INCLUDE_JET_GRID_FORWARD_EULER_DIFFUSION_SOLVER3_H_

#include <jet/constant_scalar_field3.h>
#include <jet/grid_diffusion_solver3.h>
#include <limits>
#include <memory>

namespace jet {

class GridForwardEulerDiffusionSolver3 final : public GridDiffusionSolver3 {
 public:
    GridForwardEulerDiffusionSolver3();

    void solve(
        const ScalarGrid3& source,
        double diffusionCoefficient,
        double timeIntervalInSeconds,
        ScalarGrid3* dest,
        const ScalarField3& boundarySdf
            = ConstantScalarField3(kMaxD),
        const ScalarField3& fluidSdf
            = ConstantScalarField3(-kMaxD)) override;

    void solve(
        const CollocatedVectorGrid3& source,
        double diffusionCoefficient,
        double timeIntervalInSeconds,
        CollocatedVectorGrid3* dest,
        const ScalarField3& boundarySdf
            = ConstantScalarField3(kMaxD),
        const ScalarField3& fluidSdf
            = ConstantScalarField3(-kMaxD)) override;

    void solve(
        const FaceCenteredGrid3& source,
        double diffusionCoefficient,
        double timeIntervalInSeconds,
        FaceCenteredGrid3* dest,
        const ScalarField3& boundarySdf
            = ConstantScalarField3(kMaxD),
        const ScalarField3& fluidSdf
            = ConstantScalarField3(-kMaxD)) override;

 private:
    Array3<char> _markers;

    void buildMarkers(
        const Size3& size,
        const std::function<Vector3D(size_t, size_t, size_t)>& pos,
        const ScalarField3& boundarySdf,
        const ScalarField3& fluidSdf);
};

typedef std::shared_ptr<GridForwardEulerDiffusionSolver3>
    GridForwardEulerDiffusionSolver3Ptr;

}  // namespace jet

#endif  // INCLUDE_JET_GRID_FORWARD_EULER_DIFFUSION_SOLVER3_H_