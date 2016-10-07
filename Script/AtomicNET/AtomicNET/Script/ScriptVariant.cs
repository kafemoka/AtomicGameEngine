

using System;
using System.Runtime.InteropServices;

namespace AtomicEngine
{
    public partial class ScriptVariant : RefCounted
    {
        public ScriptVariant(Vector2 value) :this()
        {
            SetVector2(value);
        }

        public static implicit operator ScriptVariant(Vector2 value)  // Vector2
        {
            return new ScriptVariant(value);
        }

    }

}

