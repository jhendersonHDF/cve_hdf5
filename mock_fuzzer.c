#include <stdio.h>

#include "hdf5.h"

int
main(int argc, char **argv)
{
    hid_t file_id = H5I_INVALID_HID;
    hid_t dset_id = H5I_INVALID_HID;
    hid_t attr_id = H5I_INVALID_HID;

    if (argc < 2) {
        fprintf(stderr, "usage: %s <filename.h5> <dsetname>\n", argv[0]);
        return -1;
    }

    file_id = H5Fopen(argv[1], H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id < 0) {
        fprintf(stderr, "couldn't open file '%s'\n", argv[1]);
        goto error;
    }

    if (argc == 3)
        dset_id = H5Dopen2(file_id, argv[2], H5P_DEFAULT);
    else
        dset_id = H5Dopen2(file_id, "dsetname", H5P_DEFAULT);

    if (dset_id >= 0) {
        attr_id = H5Aopen_name(dset_id, "theattr");
        if (attr_id >= 0)
            H5Aclose(attr_id);

        H5Dclose(dset_id);
    }

    H5Fclose(file_id);

    return 0;

error:
    H5E_BEGIN_TRY
    {
        H5Aclose(attr_id);
        H5Dclose(dset_id);
        H5Fclose(file_id);
    }
    H5E_END_TRY

    return -1;
}
