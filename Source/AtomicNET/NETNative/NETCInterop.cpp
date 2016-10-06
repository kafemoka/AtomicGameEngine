
#include <Atomic/Script/ScriptVariantMap.h>
#include <Atomic/IPC/IPC.h>

#include <Atomic/Graphics/VertexBuffer.h>
#include <Atomic/Graphics/Viewport.h>
#include <Atomic/Graphics/Graphics.h>
#include <Atomic/Graphics/Camera.h>
#include <Atomic/Graphics/Light.h>
#include <Atomic/Graphics/Octree.h>


#include "NETCore.h"

#ifdef ATOMIC_PLATFORM_WINDOWS
#define ATOMIC_EXPORT_API __declspec(dllexport)
#else
#define ATOMIC_EXPORT_API
#endif

// TODO: Split into separate module files

// IMPORTANT: methods here are prefaced with csi_ instead of csb_, the later being automatically generated bindings

namespace Atomic
{

#ifdef ATOMIC_PLATFORM_IOS
    static const char *sdlResourceDir = 0;
    static const char *sdlDocumentsDir = 0;
#endif

    extern "C"
    {

        ATOMIC_EXPORT_API ClassID csi_Atomic_RefCounted_GetClassID(RefCounted* refCounted)
        {
            if (!refCounted)
                return 0;

            return refCounted->GetClassID();
        }

        ATOMIC_EXPORT_API void csi_AtomicEngine_ReleaseRef(RefCounted* refCounted)
        {
            if (!refCounted)
                return;

            refCounted->ReleaseRef();
        }

        ATOMIC_EXPORT_API const char* csi_Atomic_AObject_GetTypeName(Object* self)
        {

            static String returnValue;
            returnValue = self->GetTypeName();
            return returnValue.CString();
        }

        ATOMIC_EXPORT_API int csi_Atomic_RefCounted_Refs(RefCounted* self)
        {
            return self->Refs();
        }


        ATOMIC_EXPORT_API void csi_Atomic_AObject_SendEvent(Object* obj, const char* eventType, ScriptVariantMap* vmap)
        {
            obj->SendEvent(eventType, vmap ? vmap->GetVariantMap() : obj->GetEventDataMap());
        }

        ATOMIC_EXPORT_API ClassID csi_Atomic_NETCore_Initialize(NETCoreEventDispatchFunction eventDispatch, NETCoreUpdateDispatchFunction updateDispatch)
        {
            Context* context = new Context();

            // NOTE: We don't simply marshal the NETCoreDelegates structure due to iOS "reverse callback" limitation
            NETCoreDelegates delegates;
            delegates.eventDispatch = eventDispatch;
            delegates.updateDispatch = updateDispatch;

            NETCore* netCore = new NETCore(context, &delegates);
            context->RegisterSubsystem(netCore);
            return netCore;
        }

        ATOMIC_EXPORT_API unsigned csi_Atomic_AtomicNET_StringToStringHash(const char* str)
        {
            unsigned hash = 0;

            if (!str)
                return hash;

            while (*str)
            {
                // Perform the actual hashing as case-insensitive
                char c = *str;
                hash = SDBMHash(hash, (unsigned char)tolower(c));
                ++str;
            }

            return hash;
        }

        ATOMIC_EXPORT_API void csi_Atomic_AtomicNET_ScriptVariantMapCopyVariantMap(ScriptVariantMap* svm, VariantMap* vm)
        {
            if (!svm)
                return;

            if (!vm)
            {
                svm->CopySourceVariantMap(Variant::emptyVariantMap);
                return;
            }

            svm->CopySourceVariantMap(*vm);

        }

        ATOMIC_EXPORT_API void* csi_Atomic_AtomicNET_ScriptVariantMap_GetVoidPtr(ScriptVariantMap* svm, const char* key)
        {
            if (!svm || !key || !strlen(key))
                return nullptr;

            return svm->GetVoidPtr(key);

        }

        // IPC
        ATOMIC_EXPORT_API void csi_Atomic_IPC_SendEventToBrokerWithEventData(IPC* ipc, const char* eventType, ScriptVariantMap* variantMap)
        {

#ifdef ATOMIC_PLATFORM_DESKTOP
            if (variantMap)
                ipc->SendEventToBroker(eventType, variantMap->GetVariantMap());
            else
                ipc->SendEventToBroker(eventType);
#endif

        }

        // Graphics

        ATOMIC_EXPORT_API void* csi_Atomic_Graphics_GetSDLWindow()
        {
            if (!NETCore::GetContext())
                return 0;

            if (!NETCore::GetContext()->GetSubsystem<Graphics>())
                return 0;

            return NETCore::GetContext()->GetSubsystem<Graphics>()->GetSDLWindow();

        }

        ATOMIC_EXPORT_API void* csi_Atomic_VertexBuffer_Lock(VertexBuffer* vb, unsigned start, unsigned count, bool discard)
        {
            if (!vb)
                return nullptr;

            return vb->Lock(start, count, discard);

        }

        ATOMIC_EXPORT_API void csi_Atomic_Graphics_SetShaderParameter_Matrix3x4(Graphics* graphics, const char* param, Matrix3x4* matrix)
        {
            if (!graphics || !param || !strlen(param))
                return;

            graphics->SetShaderParameter(param, *matrix);
        }

        // Light

        ATOMIC_EXPORT_API void csi_Atomic_Light_SetShadowBias(Light* light, BiasParameters* parameters)
        {
            if (!parameters)
                return;

            light->SetShadowBias(*parameters);

        }

        ATOMIC_EXPORT_API void csi_Atomic_Light_GetShadowBias(Light* light, BiasParameters* parameters)
        {
            if (!parameters)
                return;

            *parameters = light->GetShadowBias();

        }


        ATOMIC_EXPORT_API void csi_Atomic_Light_SetShadowCascade(Light* light, CascadeParameters* parameters)
        {
            if (!parameters)
                return;

            light->SetShadowCascade(*parameters);

        }

        ATOMIC_EXPORT_API void csi_Atomic_Light_GetShadowCascade(Light* light, CascadeParameters* parameters)
        {
            if (!parameters)
                return;

            *parameters = light->GetShadowCascade();

        }


        ATOMIC_EXPORT_API void csi_Atomic_Light_SetShadowFocus(Light* light, FocusParameters* parameters)
        {
            if (!parameters)
                return;

            light->SetShadowFocus(*parameters);

        }

        ATOMIC_EXPORT_API void csi_Atomic_Light_GetShadowFocus(Light* light, FocusParameters* parameters)
        {
            if (!parameters)
                return;

            *parameters = light->GetShadowFocus();
        }

        // Camera

        ATOMIC_EXPORT_API void csi_Atomic_Camera_GetScreenRay(Camera* camera, float x, float y, Ray* ray)
        {
            if (!camera || !ray)
                return;

            *ray = camera->GetScreenRay(x, y);
        }

        // Octree

        ATOMIC_EXPORT_API void csi_Atomic_Octree_Raycast_FreeResult(PODVector<RayQueryResult>* resultVector)
        {
            delete resultVector;
        }
    

        // Any result vector must be freed with csi_Atomic_Octree_Raycast_FreeResult
        ATOMIC_EXPORT_API RayQueryResult* csi_Atomic_Octree_Raycast(Octree *octree, const Ray& ray, const RayQueryLevel& level, float maxDistance, unsigned int flags, unsigned int viewMask,
            bool single, void** resultVector, int *count) 
        {
            PODVector<RayQueryResult>* results = new PODVector<RayQueryResult>();

            *count = 0;
            *resultVector = 0;

            RayOctreeQuery query(*results, ray, level, maxDistance, flags, viewMask);
            
            if (single)
                octree->RaycastSingle(query);
            else
                octree->Raycast(query);

            if (results->Size() == 0)
            {
                delete results;
                return NULL;
            }

            *count = results->Size();
            *resultVector = results;
            return &(*results)[0];
        }

        


#ifdef ATOMIC_PLATFORM_IOS
        ATOMIC_EXPORT_API void SDL_IOS_Init(const char *resourceDir, const char *documentsDir)
        {
            sdlResourceDir = resourceDir;
            sdlDocumentsDir = documentsDir;
        }
#endif


    }
}

#ifdef ATOMIC_PLATFORM_IOS

//FileSystem.cpp uses these functions as external.
const char* SDL_IOS_GetResourceDir()
{
    return Atomic::sdlResourceDir;
}

const char* SDL_IOS_GetDocumentsDir()
{
    return Atomic::sdlDocumentsDir;
}

#endif






