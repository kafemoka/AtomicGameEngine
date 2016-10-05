using System;
namespace AtomicEngine
{

    public partial class CSComponent : ScriptComponent
    {

        public override string GetTypeName()
        {
            return GetType().Name;
        }

        public T GetComponent<T>(bool recursive = false) where T : Component
        {
            return Node.GetComponent<T>(recursive);
        }

    }

}
