/*
 * Copyright (c) 2010 Cisco Systems, Inc.  All rights reserved.
 * Copyright © 2010-2011 UT-Battelle, LLC. All rights reserved.
 * Copyright © 2010-2011 Oak Ridge National Labs.  All rights reserved.
 *
 * See COPYING in top-level directory
 *
 * $COPYRIGHT$
 *
 */

#include "cci/config.h"

#include <stdio.h>

#include "cci.h"
#include "plugins/core/core.h"


int cci_rma_register(cci_endpoint_t *endpoint,
                     cci_connection_t *connection,
                     void *start, uint64_t length,
                     uint64_t *rma_handle)
{
    cci__conn_t *conn = NULL;

    if (NULL == endpoint ||
        NULL == rma_handle ||
        NULL == start ||
        0ULL == length) {
        return CCI_EINVAL;
    }

    if (connection) {
        conn = container_of(connection, cci__conn_t, connection);
        if (!cci_conn_is_reliable(conn)) {
            debug(CCI_DB_INFO, "%s: RMA registration requires a reliable "
                               "connection", __func__);
            return CCI_EINVAL;
        }
    }

    return cci_core->rma_register(endpoint, connection, start, length, rma_handle);
}
