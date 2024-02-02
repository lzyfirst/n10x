/*
 * Copyright © 2015 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Authors:
 *    Rafael Antognolli <rafael.antognolli@intel.com>
 *
 */

#include <linux/module.h>

#include "drm_crtc_helper_internal.h"

MODULE_AUTHOR("David Airlie, Jesse Barnes");
MODULE_DESCRIPTION("DRM KMS helper");
MODULE_LICENSE("GPL and additional rights");

static int __init drm_kms_helper_init(void)
{
	/*
	 * The Kconfig DRM_KMS_HELPER selects FRAMEBUFFER_CONSOLE (if !EXPERT)
	 * but the module doesn't depend on any fb console symbols.  At least
	 * attempt to load fbcon to avoid leaving the system without a usable
	 * console.
	 */
	if (IS_ENABLED(CONFIG_DRM_FBDEV_EMULATION) &&
	    IS_MODULE(CONFIG_FRAMEBUFFER_CONSOLE) &&
	    !IS_ENABLED(CONFIG_EXPERT))
		request_module_nowait("fbcon");

	return drm_dp_aux_dev_init();
}

static void __exit drm_kms_helper_exit(void)
{
	/* Call exit functions from specific kms helpers here */
	drm_dp_aux_dev_exit();
}

module_init(drm_kms_helper_init);
module_exit(drm_kms_helper_exit);
