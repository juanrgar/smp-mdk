#include "UuidTest.h"

#include "Mdk/SimpleTypes.h"

using namespace Smp::Mdk;

void
UuidTest::setUp(void)
{}

void
UuidTest::tearDown(void)
{}

void
UuidTest::testConstructors(void)
{
  {
    Uuid uuid;
    CPPUNIT_ASSERT_EQUAL(Smp::UInt32(0), uuid.Data1);
    CPPUNIT_ASSERT_EQUAL(Smp::UInt16(0), uuid.Data2);
    CPPUNIT_ASSERT_EQUAL(Smp::UInt16(0), uuid.Data3);
    for (Smp::UInt32 i(0); i != 8; ++i) {
      CPPUNIT_ASSERT_EQUAL(Smp::UInt8(0), uuid.Data4[i]);
    }
  }

  {
    Uuid uuid(NullUuid);
    CPPUNIT_ASSERT_EQUAL(Smp::UInt32(0), uuid.Data1);
    CPPUNIT_ASSERT_EQUAL(Smp::UInt16(0), uuid.Data2);
    CPPUNIT_ASSERT_EQUAL(Smp::UInt16(0), uuid.Data3);
    for (Smp::UInt32 i(0); i != 8; ++i) {
      CPPUNIT_ASSERT_EQUAL(Smp::UInt8(0), uuid.Data4[i]);
    }
  }

  {
    Uuid uuid("00112233-4455-6677-8899-AABBCCDDEEFF");
    CPPUNIT_ASSERT_EQUAL(Smp::UInt32(0x00112233), uuid.Data1);
    CPPUNIT_ASSERT_EQUAL(Smp::UInt16(0x4455), uuid.Data2);
    CPPUNIT_ASSERT_EQUAL(Smp::UInt16(0x6677), uuid.Data3);
    CPPUNIT_ASSERT_EQUAL(Smp::UInt8(0x88), uuid.Data4[0]);
    CPPUNIT_ASSERT_EQUAL(Smp::UInt8(0x99), uuid.Data4[1]);
    CPPUNIT_ASSERT_EQUAL(Smp::UInt8(0xAA), uuid.Data4[2]);
    CPPUNIT_ASSERT_EQUAL(Smp::UInt8(0xBB), uuid.Data4[3]);
    CPPUNIT_ASSERT_EQUAL(Smp::UInt8(0xCC), uuid.Data4[4]);
    CPPUNIT_ASSERT_EQUAL(Smp::UInt8(0xDD), uuid.Data4[5]);
    CPPUNIT_ASSERT_EQUAL(Smp::UInt8(0xEE), uuid.Data4[6]);
    CPPUNIT_ASSERT_EQUAL(Smp::UInt8(0xFF), uuid.Data4[7]);
  }
}

void
UuidTest::testGetSet(void)
{
  {
    Smp::Bool res = false;

    Uuid uuid;

    uuid.Set("00112233-4455-6677-8899-AABBCCDDEEFF");
    CPPUNIT_ASSERT_EQUAL(Smp::UInt32(0x00112233), uuid.Data1);
    CPPUNIT_ASSERT_EQUAL(Smp::UInt16(0x4455), uuid.Data2);
    CPPUNIT_ASSERT_EQUAL(Smp::UInt16(0x6677), uuid.Data3);
    CPPUNIT_ASSERT_EQUAL(Smp::UInt8(0x88), uuid.Data4[0]);
    CPPUNIT_ASSERT_EQUAL(Smp::UInt8(0x99), uuid.Data4[1]);
    CPPUNIT_ASSERT_EQUAL(Smp::UInt8(0xAA), uuid.Data4[2]);
    CPPUNIT_ASSERT_EQUAL(Smp::UInt8(0xBB), uuid.Data4[3]);
    CPPUNIT_ASSERT_EQUAL(Smp::UInt8(0xCC), uuid.Data4[4]);
    CPPUNIT_ASSERT_EQUAL(Smp::UInt8(0xDD), uuid.Data4[5]);
    CPPUNIT_ASSERT_EQUAL(Smp::UInt8(0xEE), uuid.Data4[6]);
    CPPUNIT_ASSERT_EQUAL(Smp::UInt8(0xFF), uuid.Data4[7]);
  }

  {
    Smp::Bool res = false;
    Smp::Char8* uuidRet = new Smp::Char8[Uuid::BUFFER_SIZE];
    const Smp::Char8* myUuid = "00112233-4455-6677-8899-AABBCCDDEEFF";

    Uuid uuid("00112233-4455-6677-8899-AABBCCDDEEFF");
    uuid.Get(uuidRet);

    CPPUNIT_ASSERT_EQUAL(0, ::strcmp(uuidRet, myUuid));

    delete[] uuidRet;
  }

  {
    Smp::Bool res = false;
    Uuid uuid;
    res = uuid.Set("00");
    CPPUNIT_ASSERT_EQUAL(false, res);
    printf("0x%x\n", uuid.Data1);
  }
}
