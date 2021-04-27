#include <platform_def.h>
#include <arch.h>
#include <plat/common/platform.h>

static const unsigned char plat_power_domain_tree_desc[PLAT_MAX_PWR_LVL + 1] = {
	/* One root node for the SoC */
	1,
	/* One node for each cluster */
	PLATFORM_CLUSTER_COUNT,
	/* One set of CPUs per cluster */
	PLATFORM_MAX_CPUS_PER_CLUSTER,
};

int plat_core_pos_by_mpidr(u_register_t mpidr)
{
	unsigned int core = MPIDR_AFFLVL1_VAL(mpidr); /* MPIDR : 8100_0x00, x=0~3 */
	return core;
}

const unsigned char *plat_get_power_domain_tree_desc(void)
{
	return plat_power_domain_tree_desc;
}
