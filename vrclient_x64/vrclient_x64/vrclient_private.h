#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#include <linux/limits.h>

#ifndef __cplusplus
#include "unixlib.h"
#include "wine/debug.h"
#include "cxx.h"
#else
typedef void (*vtable_ptr)(void);
#endif

#if __cplusplus
extern "C" {
#endif

char *json_convert_paths(const char *input);
char *json_convert_startup_info(const char *startup_info);

char *vrclient_dos_to_unix_path( const char *src );
void vrclient_free_path( const char *path );

#if __cplusplus
}
#endif

unsigned int vrclient_unix_path_to_dos_path(bool api_result, const char *src, char *dst, uint32_t dst_bytes);
void *create_LinuxMatchmakingServerListResponse(void *win);

#ifndef __cplusplus
typedef struct ID3D11Device ID3D11Device;
typedef struct IDXGIVkInteropDevice IDXGIVkInteropDevice;

struct client_core_data
{
    CRITICAL_SECTION critical_section;
    struct generic_interface *created_interfaces;
    SIZE_T created_interface_count;
    SIZE_T created_interfaces_size;
};

struct compositor_data
{
    ID3D11Device *d3d11_device;
    IDXGIVkInteropDevice *dxvk_device;
    BOOL d3d11_explicit_handoff, handoff_called;
    void *client_core_linux_side;

#ifndef __x86_64__
    /* Digital action state change fixup hack. */
    struct
    {
        uint64_t action;
        uint64_t origin;
        LARGE_INTEGER update_qpf_time;
        BOOL previous_state;
    } digital_actions_state[128];
    unsigned int digital_action_count;
    LARGE_INTEGER qpf_freq;
#endif
};

extern struct compositor_data compositor_data;

struct w_steam_iface
{
    vtable_ptr *vtable;
    void *u_iface;
    union
    {
        struct client_core_data user_data; /* for IVRClientCore */
    };
};

struct w_steam_iface *create_win_interface(const char *name, void *linux_side);

struct generic_interface
{
    struct w_steam_iface *object;
    void (*dtor)(struct w_steam_iface *);
};

#ifdef __dxvk_interop_h__
extern w_Texture_t vrclient_translate_texture_dxvk( const w_Texture_t *texture, w_VRVulkanTextureData_t *vkdata,
                                                    IDXGIVkInteropSurface *dxvk_surface, IDXGIVkInteropDevice **p_dxvk_device,
                                                    VkImageLayout *image_layout, VkImageCreateInfo *image_info );
#endif /* __dxvk_interop_h__ */

extern VkDevice_T *get_native_VkDevice( VkDevice_T *device );
extern VkInstance_T *get_native_VkInstance( VkInstance_T *instance );
extern VkPhysicalDevice_T *get_native_VkPhysicalDevice( VkPhysicalDevice_T *device );
extern VkPhysicalDevice_T *get_wrapped_VkPhysicalDevice( VkInstance_T *instance, VkPhysicalDevice_T *device );
extern VkQueue_T *get_native_VkQueue( VkQueue_T *queue );

#endif  /* __cplusplus */
