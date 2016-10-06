
using System;
using System.Runtime.InteropServices;

namespace AtomicEngine
{
    public partial class Camera : Component
    {
       
        /// Return ray corresponding to normalized screen coordinates (0 - 1), with origin on the near clip plane.
        public Ray GetScreenRay(float x, float y)
        {
            csi_Atomic_Camera_GetScreenRay(nativeInstance, x, y, ref GetScreenRayReturnValue);
            return GetScreenRayReturnValue;
        }

        private Ray GetScreenRayReturnValue = new Ray();
        [DllImport(Constants.LIBNAME, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private static extern void csi_Atomic_Camera_GetScreenRay(IntPtr self, float x, float y, ref Ray retValue);

    };

}

