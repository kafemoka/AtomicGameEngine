using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace AtomicEngine
{
    public delegate void EventDelegate(uint eventType, ScriptVariantMap eventData);

    public delegate void SenderEventDelegate(AObject sender, uint eventType, ScriptVariantMap eventData);

    public delegate void NativeEventDelegate(NativeEventData eventData);
    public delegate void NativeEventDelegate<T>(T eventData);

    public partial class ScriptVariantMap
    {
        public void CopyVariantMap(IntPtr vm)
        {
            csi_Atomic_AtomicNET_ScriptVariantMapCopyVariantMap(nativeInstance, vm);
        }

        [DllImport(Constants.LIBNAME, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private static extern IntPtr csi_Atomic_AtomicNET_ScriptVariantMapCopyVariantMap(IntPtr svm, IntPtr vm);

    }

    public class NativeEventData 
    {
        public ScriptVariantMap scriptMap;
    }

    public static partial class NativeEvents
    {
        public static uint GetEventID<T>() where T : NativeEventData
        {
            uint eventID;

            if (eventIDLookup.TryGetValue(typeof(T), out eventID))
            {
                return eventID;
            }

            return 0;
        }

        public static void RegisterEventID<T>(string eventName) where T : NativeEventData
        {
            var eventID = AtomicNET.StringToStringHash(eventName);
            var type = typeof(T);

            eventIDLookup[type] = eventID;
            typeLookup[eventID] = type;
        }

        public static NativeEventData InstantiateNativeEventData(uint eventID, ScriptVariantMap eventMap)
        {
            Type dataType;

            if (typeLookup.TryGetValue(eventID, out dataType))
            {
                NativeEventData eventData = (NativeEventData) Activator.CreateInstance(dataType);
                if (eventData.GetType() == typeof(KeyDownEventData))
                {
                    eventData.scriptMap = eventMap;
                }
                eventData.scriptMap = eventMap;
                return eventData;
            }

            return null;
        }


        static Dictionary<Type, uint> eventIDLookup = new Dictionary<Type, uint>();
        static Dictionary<uint, Type> typeLookup = new Dictionary<uint, Type>();
    }

}