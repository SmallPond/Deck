/*
 * MIT License
 * Copyright (c) 2021 _VIFEXTech
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef __PAGE_BASE_H
#define __PAGE_BASE_H

#include "lvgl.h"

/* Generate stash area data */
#define PAGE_STASH_MAKE(data) {&(data), sizeof(data)}

/* Get the data in the stash area */
#define PAGE_STASH_POP(data)  this->GetStash(&(data), sizeof(data))

class PageManager;

class PageBase
{
public:

    /* Page state */
    typedef enum
    {
        PAGE_STATE_IDLE,
        PAGE_STATE_LOAD,
        PAGE_STATE_WILL_APPEAR,
        PAGE_STATE_DID_APPEAR,
        PAGE_STATE_ACTIVITY,
        PAGE_STATE_WILL_DISAPPEAR,
        PAGE_STATE_DID_DISAPPEAR,
        PAGE_STATE_UNLOAD,
        _PAGE_STATE_LAST
    } State_t;

    /* Data area */
    typedef struct
    {
        void* ptr;
        uint32_t size;
    } Stash_t;

    /* Page switching animation properties */
    typedef struct
    {
        uint8_t Type;
        uint16_t Time;
        lv_anim_path_cb_t Path;
    } AnimAttr_t;

public:
    lv_obj_t* root;       // UI root node
    PageManager* Manager; // Page manager pointer
    const char* Name;     // Page name
    uint16_t ID;          // Page ID
    void* UserData;       // User data pointer

    /* Private data, Only page manager access */
    struct
    {
        bool ReqEnableCache;        // Cache enable request
        bool ReqDisableAutoCache;   // Automatic cache management enable request

        bool IsDisableAutoCache;    // Whether it is automatic cache management
        bool IsCached;              // Cache enable

        Stash_t Stash;              // Stash area
        State_t State;              // Page state

        /* Animation state  */
        struct
        {
            bool IsEnter;           // Whether it is the entering party
            bool IsBusy;            // Whether the animation is playing
            AnimAttr_t Attr;        // Animation properties
        } Anim;
    } priv;

public:
    virtual ~PageBase() {}

    /* Synchronize user-defined attribute configuration */
    virtual void onCustomAttrConfig() {}

    /* Page load */
    virtual void onViewLoad() {}

    /* Page load complete */
    virtual void onViewDidLoad() {}

    /* Page will be displayed soon  */
    virtual void onViewWillAppear() {}

    /* The page is displayed  */
    virtual void onViewDidAppear() {}

    /* Page is about to disappear */
    virtual void onViewWillDisappear() {}

    /* Page disappeared complete  */
    virtual void onViewDidDisappear() {}

    /* Page uninstall complete  */
    virtual void onViewDidUnload() {}

    /* Set whether to manually manage the cache */
    void SetCustomCacheEnable(bool en)
    {
        SetCustomAutoCacheEnable(false);
        priv.ReqEnableCache = en;
    }

    /* Set whether to enable automatic cache */
    void SetCustomAutoCacheEnable(bool en)
    {
        priv.ReqDisableAutoCache = !en;
    }

    /* Set custom animation properties  */
    void SetCustomLoadAnimType(
        uint8_t animType,
        uint16_t time = 500,
        lv_anim_path_cb_t path = lv_anim_path_ease_out
    )
    {
        priv.Anim.Attr.Type = animType;
        priv.Anim.Attr.Time = time;
        priv.Anim.Attr.Path = path;
    }

    /* Get the data in the stash area */
    bool GetStash(void* ptr, uint32_t size)
    {
        bool retval = false;
        if (priv.Stash.ptr != nullptr && priv.Stash.size == size)
        {
            memcpy(ptr, priv.Stash.ptr, priv.Stash.size);
            //lv_mem_free(priv.Stash.ptr);
            //priv.Stash.ptr = nullptr;
            retval = true;
        }
        return retval;
    }
};

#endif // ! __PAGE_BASE_H
