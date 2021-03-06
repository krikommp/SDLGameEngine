//
// Created by chenyifei on 2022/1/14.
//

#ifndef SDLGAMEENGINE_MYAPPENGINE_H
#define SDLGAMEENGINE_MYAPPENGINE_H

#include <AppEngine.h>

const std::string RootPath(ROOTPATH);

namespace Chapter01 {
    class WireframeApp : public AppEngine {
    protected:
        void OnStart() override;

        void OnUpdate() override;

        void OnExit() override;
    };
}

namespace Chapter02 {
    class DrawTriangleApp : public AppEngine {
    protected:
        void OnStart() override;

        void OnUpdate() override;

        void OnExit() override;
    };
}

namespace Chapter03 {
    class PerspectiveProjectionApp : public AppEngine {
    protected:
        void OnStart() override;

        void OnUpdate() override;

        void OnExit() override;
    };

    class PerspectiveModelApp : public AppEngine {
    protected:
        void OnStart() override;

        void OnUpdate() override;

        void OnExit() override;
    };
}



#endif //SDLGAMEENGINE_MYAPPENGINE_H
