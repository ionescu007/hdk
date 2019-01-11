# hdk -- Hyper-V Development Kit

The HDK is an updated version of the HvGdk.h header file published under MSR-LA as part of the Singularity Research Kernel. It has been updated to add the latest definitions, structures and definitions as described in the Microsoft Hypervisor Top-Level Functional Specification (TLFS) 5.0c published June 2018.

_Windows® and Hyper-V® are registered trademarks of Microsoft® Corporation. This repository and its contents are not sponsored or endorsed by the companies mentioned herein._

## Motivation

Developing against Hyper-V is difficult enough without symbols, and we are lucky that the HvGdk.H "leaked" at least once, and that the TLFS 5.0c exists. Unfortunately, the HvGdk.h is quite old, and the TLFS is always delayed by about a year, and does not contain readily usable definitions for programming.

## Input Data

The original HvGdk.h is modified with the following information:

* Publicly available definitions/structures defined in the HvGdk.h that shipped with the Windows Driver Kit for Windows 7
* Publicly available definitions/structures defined in the TLFS -- up to 5.0c for now
  * This also includes inferred data from the TLFS -- for example, hypercalls are documented with their raw parameter/register mapping, but HvGdk.h contains data structures for each call -- these data structures are updated based on the parameter documentation in the TLFS.
* Publicly available symbol data, when present, from the kernel and certain user-mode binaries

## Contributions

This is an ongoing header, and I may have missed many things/made transcription mistakes. Contributions and pull requests are welcome as long as you stay within the confines of the MSR-LA.

Please do not add any proprietary or intellectual property information, as this would pollute the repository. All PRs will be examined for 'sourcing' information and verified to be publicly available.

## License / Legal

Based upon my reading of the MSR-LA, it is perfectly legal to redistribute the original header file with modifications, as long as the copyright is kept (it is), modifications are clear, annotated, and date (they are), and you agree to the original license (academic/research use only). I am not a lawyer, so please consult with one if you intend to use this in any way -- but this repository and my changes appear to be covered by MSR-LA.

Please review LICENSE.MD for the full license.
