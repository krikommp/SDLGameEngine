#ifndef _ENGINETYPES_H_
#define _ENGINETYPES_H_

namespace EWorldType
{
    enum Type
    {

        None,

        /** 游戏世界 */
        Game,

        /** 编辑器世界 */
        Editor,

        /** 在编辑器中运行 */
        PIE,

        /** 编辑器预览 */
        EditorPreview,

        /** 游戏预览 */
        GamePreview
    };
}

namespace EBrowseReturnVal{
    enum Type{
        Success,

        Failure,

        Pending
    };
}

#endif //  _ENGINETYPES_H_