<?xml version="1.0" encoding="utf-8"?>
<fx:flux-document xmlns:fx="http://www.bosch.com/Flux/Model" xmlns:b="http://www.bosch.com/Flux/Model/Base" xmlns:tv="http://www.bosch.com/Flux/Model/Base/TaggedValues" xmlns:types="http://www.bosch.com/Flux/Model/Base/Types" xmlns:statistics="http://www.bosch.com/Flux/Model/Base/Statistics" xmlns:cmp="http://www.bosch.com/Flux/Model/Components" xmlns:cs="http://www.bosch.com/Flux/Model/Constraints" xmlns:dsc="http://www.bosch.com/Flux/Model/Descriptions" xmlns:cnt="http://www.bosch.com/Flux/Model/Descriptions/Content" xmlns:dd="http://www.bosch.com/Flux/Model/DetailedDesign" xmlns:doc="http://www.bosch.com/Flux/Model/Document" xmlns:ev="http://www.bosch.com/Flux/Model/Events" xmlns:hw="http://www.bosch.com/Flux/Model/Hardware" xmlns:imp="http://www.bosch.com/Flux/Model/Implementations" xmlns:map="http://www.bosch.com/Flux/Model/Mapping" xmlns:middle="http://www.bosch.com/Flux/Model/MiddleWare" xmlns:os="http://www.bosch.com/Flux/Model/OperatingSystems" xmlns:req="http://www.bosch.com/Flux/Model/Requirements" xmlns:sw="http://www.bosch.com/Flux/Model/Software" xmlns:gph="http://www.bosch.com/Flux/Model/Software/Graph" xmlns:hsm="http://www.bosch.com/Flux/Model/Software/HSM" xmlns:lab="http://www.bosch.com/Flux/Model/Software/Labels" xmlns:prc="http://www.bosch.com/Flux/Model/Software/Processes" xmlns:expr="http://www.bosch.com/Flux/Model/Software/Expressions" xmlns:stm="http://www.bosch.com/Flux/Model/Stimuli" xmlns:u="http://www.bosch.com/Flux/Model/Units" xmlns:val="http://www.bosch.com/Flux/Model/Validation" xmlns:var="http://www.bosch.com/Flux/Model/Variations" version="0.9">
  <component-model>
    <components>
      <component-type name="nrc2/if/iwd">
        <description>
          <sections>
            <section section-type="dsc.section-type:main" />
          </sections>
        </description>
        <variation-restrictions>
          <variation>var.variation-point:nrc2%2fif%2fiwd%2fbuild/var.variation:hw</variation>
          <variation>var.variation-point:nrc2%2fif%2fiwd%2fbuild/var.variation:utf</variation>
        </variation-restrictions>
      </component-type>
    </components>
  </component-model>
  <implementation-model>
    <composites>
      <implementation-composite-type name="nrc2/if/iwd/inc">
        <modules>
          <module-member member-type="imp.module-type:nrc2%2fif%2fiwd%2finc%2fiwd_responder" />
          <module-member member-type="imp.module-type:nrc2%2fif%2fiwd%2finc%2fiwd_partial_response_interface" />
          <module-member member-type="imp.module-type:nrc2%2fif%2fiwd%2finc%2fiwd_variant_release" />
          <module-member member-type="imp.module-type:nrc2%2fif%2fiwd%2finc%2fiwd_variant_debug" />
        </modules>
      </implementation-composite-type>
      <implementation-composite-type name="nrc2/if/iwd/src">
        <modules>
          <module-member member-type="imp.module-type:nrc2%2fif%2fiwd%2fsrc%2fiwd_partial_response_interface" />
          <module-member member-type="imp.module-type:nrc2%2fif%2fiwd%2fsrc%2fiwd_responder_a2l" />
        </modules>
        <composites>
          <implementation-composite-member member-type="imp.implementation-composite-type:nrc2%2fif%2fiwd%2fsrc%2fbase" />
          <implementation-composite-member member-type="imp.implementation-composite-type:nrc2%2fif%2fiwd%2fsrc%2fplus" />
        </composites>
      </implementation-composite-type>
      <implementation-composite-type name="nrc2/if/iwd/stub">
        <modules>
          <module-member member-type="imp.module-type:nrc2%2fif%2fiwd%2fstub%2fos" />
        </modules>
        <variation-restrictions>
          <variation>var.variation-point:nrc2%2fif%2fiwd%2farch/var.variation:x86</variation>
        </variation-restrictions>
      </implementation-composite-type>
      <implementation-composite-type name="nrc2/if/iwd/src/base">
        <modules>
          <module-member member-type="imp.module-type:nrc2%2fif%2fiwd%2fsrc%2fbase%2fiwd_responder" />
        </modules>
        <variation-restrictions>
          <variation>var.variation-point:nrc2%2fif%2fiwd%2fplatform/var.variation:base</variation>
        </variation-restrictions>
      </implementation-composite-type>
      <implementation-composite-type name="nrc2/if/iwd/src/plus">
        <modules>
          <module-member member-type="imp.module-type:nrc2%2fif%2fiwd%2fsrc%2fplus%2fiwd_responder" />
        </modules>
        <variation-restrictions>
          <variation>var.variation-point:nrc2%2fif%2fiwd%2fplatform/var.variation:plus</variation>
        </variation-restrictions>
      </implementation-composite-type>
    </composites>
    <files>
      <implementation-file-type name="../component_domain.info" />
      <implementation-file-type name="../inc/iwd_responder.hpp" />
      <implementation-file-type name="../src/iwd_responder.cpp" />
      <implementation-file-type name="../inc/iwd_partial_response_interface.hpp" />
      <implementation-file-type name="../src/iwd_partial_response_interface.cpp" />
      <implementation-file-type name="../inc/iwd_variant_release.hpp" />
      <implementation-file-type name="../inc/iwd_variant_debug.hpp" />
      <implementation-file-type name="../stub/os.h" />
      <implementation-file-type name="../src/base/iwd_responder.cpp" />
      <implementation-file-type name="../src/plus/iwd_responder.cpp" />
      <implementation-file-type name="../src/iwd_responder_a2l.cpp" />
    </files>
    <implementations>
      <implementation-type name="nrc2/if/iwd">
        <modules>
          <module-member member-type="imp.module-type:nrc2%2fif%2fiwd%2fcomponent_domain" />
        </modules>
        <composites>
          <implementation-composite-member member-type="imp.implementation-composite-type:nrc2%2fif%2fiwd%2finc" />
          <implementation-composite-member member-type="imp.implementation-composite-type:nrc2%2fif%2fiwd%2fsrc" />
          <implementation-composite-member member-type="imp.implementation-composite-type:nrc2%2fif%2fiwd%2fstub" />
        </composites>
        <custom-property-groups>
          <custom-property-group source="http://www.bosch.com/Flux/TestAndBuild">
            <tagged-values>
              <string-tagged-value name="compiler-flag-set-name" />
            </tagged-values>
          </custom-property-group>
        </custom-property-groups>
      </implementation-type>
    </implementations>
    <modules>
      <module-type name="nrc2/if/iwd/component_domain">
        <files>
          <implementation-file-member member-type="imp.implementation-file-type:..%2fcomponent_domain.info" />
        </files>
      </module-type>
      <module-type name="nrc2/if/iwd/inc/iwd_responder">
        <files>
          <implementation-file-member member-type="imp.implementation-file-type:..%2finc%2fiwd_responder.hpp" />
        </files>
      </module-type>
      <module-type name="nrc2/if/iwd/src/iwd_responder" access="private">
        <files>
          <implementation-file-member member-type="imp.implementation-file-type:..%2fsrc%2fiwd_responder.cpp" />
        </files>
      </module-type>
      <module-type name="nrc2/if/iwd/inc/iwd_partial_response_interface">
        <files>
          <implementation-file-member member-type="imp.implementation-file-type:..%2finc%2fiwd_partial_response_interface.hpp" />
        </files>
      </module-type>
      <module-type name="nrc2/if/iwd/src/iwd_partial_response_interface" access="private">
        <files>
          <implementation-file-member member-type="imp.implementation-file-type:..%2fsrc%2fiwd_partial_response_interface.cpp" />
        </files>
      </module-type>
      <module-type name="nrc2/if/iwd/inc/iwd_variant_release" alias="iwd_variant">
        <variation-restrictions>
          <variation>var.variation-point:nrc2%2fif%2fiwd%2fbuild_type/var.variation:release</variation>
        </variation-restrictions>
        <files>
          <implementation-file-member member-type="imp.implementation-file-type:..%2finc%2fiwd_variant_release.hpp" />
        </files>
      </module-type>
      <module-type name="nrc2/if/iwd/inc/iwd_variant_debug" alias="iwd_variant">
        <variation-restrictions>
          <variation>var.variation-point:nrc2%2fif%2fiwd%2fbuild_type/var.variation:debug</variation>
        </variation-restrictions>
        <files>
          <implementation-file-member member-type="imp.implementation-file-type:..%2finc%2fiwd_variant_debug.hpp" />
        </files>
      </module-type>
      <module-type name="nrc2/if/iwd/stub/os" alias="os" access="private">
        <files>
          <implementation-file-member member-type="imp.implementation-file-type:..%2fstub%2fos.h" />
        </files>
      </module-type>
      <module-type name="nrc2/if/iwd/src/base/iwd_responder">
        <files>
          <implementation-file-member member-type="imp.implementation-file-type:..%2fsrc%2fbase%2fiwd_responder.cpp" />
        </files>
      </module-type>
      <module-type name="nrc2/if/iwd/src/plus/iwd_responder">
        <files>
          <implementation-file-member member-type="imp.implementation-file-type:..%2fsrc%2fplus%2fiwd_responder.cpp" />
        </files>
      </module-type>
       <module-type name="nrc2/if/iwd/src/iwd_responder_a2l" access="private">
        <files>
          <implementation-file-member member-type="imp.implementation-file-type:..%2fsrc%2fiwd_responder_a2l.cpp" />
        </files>
      </module-type>
    </modules>
  </implementation-model>
  <mapping-model>
    <implementation-allocations>
      <implementation-allocation component="cmp.component-type:nrc2%2fif%2fiwd" implementation="imp.implementation-type:nrc2%2fif%2fiwd" />
    </implementation-allocations>
  </mapping-model>
  <requirements-model />
</fx:flux-document>