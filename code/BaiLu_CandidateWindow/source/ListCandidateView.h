#pragma once

/*
* 竖排的候选词窗口，目前暂时使用ListBox来实现
*/
#include "ICandidateView.h"

class ListCandidateView : public ICandidateView
{
public:
    ListCandidateView();
    ~ListCandidateView() override;

    bool Create(HWND parent) override;

    void SetCandidates(
        const std::vector<std::wstring>& items) override;

    int GetSelectedIndex() const override;

    void SetSelectedIndex(int index) override;

    void Resize(int width, int height) override;

private:
    HWND m_hwnd = nullptr;
};