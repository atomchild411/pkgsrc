# lefthk-core: KeySym (c_ulong) is 32 bits on ILP32 targets like IRIX n32,
# where u32::try_from() of it cannot fail and its error is Infallible:
# widen first, so the error is TryFromIntError everywhere.
s/Ok(u32::try_from(sym)?)/Ok(u32::try_from(sym as u64)?)/
