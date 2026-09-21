#pragma once

class ModelChangeListener {
public:
    virtual ~ModelChangeListener() = default;
    virtual void onModelChanged() = 0;
};
